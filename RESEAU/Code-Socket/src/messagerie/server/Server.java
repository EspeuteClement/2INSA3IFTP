package messagerie.server;

import messagerie.protocol.Message;
import messagerie.threads.MessagerieInterface;
import messagerie.threads.ThreadableSocket;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;

/** A server that run multiples sockets and manages connexions with mutltiples users.
 * Created by element on 18/12/15.
 */
public class Server implements MessagerieInterface {
    private CopyOnWriteArrayList<ThreadableSocket> ChildServers = new CopyOnWriteArrayList<ThreadableSocket>();
    private CopyOnWriteArrayList<Thread> ChildThreads = new CopyOnWriteArrayList<Thread>();
    private CopyOnWriteArrayList<Message> MessageHistory = new CopyOnWriteArrayList<Message>();

    private ConcurrentHashMap<Integer,String> UserList = new ConcurrentHashMap<Integer,String>();
    private ConcurrentHashMap<Integer,ThreadableSocket> UserSockets = new ConcurrentHashMap<>();
    private int port = 4444;

    private int userIDCount = 0;

    ServerSocket ListenSocket = null;

    public synchronized void CreateNewChild()
    {
        try
        {
            while(true)
            {
                System.err.println("Successfully spawned a new server. It's listening in the darkness ...");
                Socket theSocket = ListenSocket.accept();
                ThreadableSocket newChild = new ThreadableSocket(this, theSocket);
                Thread threadChild = new Thread(newChild);

                ChildServers.add(newChild);
                ChildThreads.add(threadChild);
                threadChild.start();

                SendHistory(newChild);
            }
        }
        catch (Exception e)
        {
            System.err.println("Couldn't spawn a new server. Will try again !");
            e.printStackTrace();
            try {
                Thread.sleep(1000);                 //1000 milliseconds is one second.
            } catch(InterruptedException ex) {
                Thread.currentThread().interrupt();
            }
            this.CreateNewChild();
        }
    }

    public void BroadcastMessage(Message msg)
    {
        for (ThreadableSocket m : ChildServers )
        {
            m.SendMessage(msg);
        }
    }

    public void SendHistory(ThreadableSocket child)
    {
        for (Message m : MessageHistory)
        {
            child.SendMessage(m);
        }
    }

    public Server(int port)
    {
        this.port = port;
        try {
            this.ListenSocket = new ServerSocket(port);
        } catch (IOException e) {
            e.printStackTrace();
        }
        this.CreateNewChild();
    }

    public static void main(String Args[])
    {
        if (Args.length != 1)
        {
            System.err.println("You must give a port number");
            return;
        }

        try
        {
            Server BroodMother = new Server(Integer.parseInt(Args[0]));
        }
        catch (Exception e)
        {

        }
    }

    @Override
    public void RecevoirMessage(ThreadableSocket instance, Message msg) {
        // Si il y a un contenu dans le message
        if (msg.message != null)
        {

            // Check if the message is a command :
            if (msg.message.charAt(0) == '/')
            {
                String[] splits = msg.message.split("\\s+");
                try{
                    // Commande '/nick nouveau_nom' pour changer de nom
                    if (splits[0].equals("/nick"))
                    {
                        if (!UserList.containsValue(splits[1]))
                        {
                            String oldName = UserList.get(msg.ID);
                            UserList.put(msg.ID,splits[1]);
                            RecevoirMessage(instance, new Message("Sever","User " + oldName + " is now know as " + splits[1],-1));
                            SendUserList();
                        }
                        else
                        {
                            // If the name is already in use, send an error message to the user.
                            instance.SendMessage(new Message("Server","Error, nickname '" + splits[1]+"' is already in use",-2));
                        }
                    }
                    // If the command is a Whisper
                    else if (splits[0].equals("/w"))
                    {
                        // We check if the user is in the UserList list
                        if (UserList.contains(splits[1]))
                        {
                            // We get the ID linked with the user
                            int id = GetNameID(splits[1]);

                            // We create the message using the rest of the splits
                            String message = splits[2];
                            for (int i = 3; i<splits.length;i++)
                            {
                                message += " "+splits[i];
                            }

                            // We get the socket linked to the user ID
                            ThreadableSocket us = UserSockets.get(id);

                            // We send a message to the send so he has a confirmation that everything went okay
                            instance.SendMessage(new Message("Whisper to " + splits[1],message,Message.SERVER_WHISPER_MSG));

                            // We send the whisper to the recipient
                            us.SendMessage(new Message("Whisper from " + UserList.get(msg.ID),message,Message.SERVER_WHISPER_MSG));
                        }
                        else
                        {
                            // If the user is not in the list, we send an error message to the sender
                            instance.SendMessage(new Message("Server","User "+splits[1]+" is not connected",Message.SERVER_ERR_MSG));
                        }
                    }
                    // Help command, simply send the help to the one that requested the help
                    else if (splits[0].equals("/help"))
                    {
                        instance.SendMessage(new Message("Server","Help\n\n '/nick new_name' : Change your name to 'new_name'\n" +
                                "'/w user_name Your message' : Send Your Message to user_name privately\n"+
                                "'/help' : Displays this help",Message.SERVER_MSG));
                    }
                    // Else we tell the user that his command is not recognised and that he should use /help to see the list
                    else
                    {
                        instance.SendMessage(new Message("Server","Error, command '" + splits[0]+"' is not recognised.\nUse /help to learn about the" +
                                " available commands",-2));
                    }
                }
                catch (ArrayIndexOutOfBoundsException e)
                {
                    System.err.println("Not enough parameters");
                    instance.SendMessage(new Message("Server","Not enough parameters",-1));
                }
            }

            // If it's a normal message, send the message to everyone
            else {
                // Fetch the user name in the UserList
                if (msg.user == null)
                {
                    msg.user = UserList.get(msg.ID);
                }
                MessageHistory.add(msg);
                BroadcastMessage(msg);
            }
        }

        else if(instance != null)
        {
            // If the message is empty and the ID is USER_LOGIN_MSG, then this is a client that request an ID
            if (msg.user == null && msg.ID == Message.USER_LOGIN_MSG)
            {
                userIDCount++;
                UserSockets.put(userIDCount,instance);

                //We send the message with a /setID that the client will understand as an ID assignation
                instance.SendMessage(new Message(null,"/setID",userIDCount));
                System.err.println("New id affected");
            }
            // Connexion de l'utilisateur
            else if (msg.ID > 0)
            {
                if (UserList.containsValue(msg.user))
                {
                    // Create a unique id for the user if the name already exists
                    msg.user = msg.user + msg.ID;
                }
                UserList.put(msg.ID,msg.user);
                instance.ID = msg.ID;
                System.err.println("User " + msg.user + " is connected");
                Message connexionMessage = new Message("Server","User " + msg.user + " is connected", -1);
                instance.SendMessage(new Message("Server","Welcome new user. Please type '/nick your_name' to change your user name",Message.SERVER_MSG));
                RecevoirMessage(null, connexionMessage);
                SendUserList();
            }

        }

    }

    public void SendUserList()
    {
        String m = "/UserList";
        for (String u : UserList.values())
        {
            m += " " + u;
        }
        BroadcastMessage(new Message("Server",m,-1));
    }

    /** Returns the ID of the user with the Name that equals name
     *
     * @param name
     * @return The ID if it has been found, or -1 if it hasn't
     */
    public int GetNameID(String name)
    {
        for (int i : UserList.keySet())
        {
            if (UserList.get(i).equals(name))
            {
                return i;
            }
        }
        return -1;
    }

    @Override
    public void Disconnect(ThreadableSocket instance, Thread thread) {

        Message connexionMessage = new Message("Server","User " + UserList.get(instance.ID) + " is disconnected", -1);
        UserList.remove(instance.ID);
        UserSockets.remove(instance.ID);
        System.err.println(connexionMessage);
        RecevoirMessage(null, connexionMessage);

        ChildServers.remove(instance);
        ChildThreads.remove(thread);

        SendUserList();
    }
}
