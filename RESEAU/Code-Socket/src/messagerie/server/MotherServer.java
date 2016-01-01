package messagerie.server;

import messagerie.protocol.Message;
import messagerie.threads.MessagerieInterface;
import messagerie.threads.SocketThread;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.SynchronousQueue;

/**
 * Created by element on 18/12/15.
 */
public class MotherServer implements MessagerieInterface {
    private CopyOnWriteArrayList<SocketThread> ChildServers = new CopyOnWriteArrayList<SocketThread>();
    private CopyOnWriteArrayList<Thread> ChildThreads = new CopyOnWriteArrayList<Thread>();
    private CopyOnWriteArrayList<Message> MessageHistory = new CopyOnWriteArrayList<Message>();

    private ConcurrentHashMap<Integer,String> UserList = new ConcurrentHashMap<Integer,String>();
    private int port = 4444;

    private int userIDCount = 0;

    ServerSocket ListenSocket = null;

    public synchronized void CreateNewChild()
    {
        try
        {
            while(true)
            {
                System.err.println("Succesfully spawned a new server. It's listening in the darkness ...");
                Socket theSocket = ListenSocket.accept();
                SocketThread newChild = new SocketThread(this, theSocket);
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
        for (SocketThread m : ChildServers )
        {
            m.SendMessage(msg);
        }
    }

    public void SendHistory(SocketThread child)
    {
        for (Message m : MessageHistory)
        {
            child.SendMessage(m);
        }
    }

    public MotherServer(int port)
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
            MotherServer BroodMother = new MotherServer(Integer.parseInt(Args[0]));
            while(true)
            {

            }
        }
        catch (Exception e)
        {

        }
    }

    @Override
    public void RecevoirMessage(SocketThread instance, Message msg) {
        // Si il y a un contenu dans le message
        if (msg.message != null)
        {

            // Check if the message is a command :
            if (msg.message.charAt(0) == '/')
            {
                String[] splits = msg.message.split("\\s+");
                try{
                    if (splits[0].equals("/nick"))
                    {
                        String oldName = UserList.get(msg.ID);
                        UserList.put(msg.ID,splits[1]);
                        instance.Name =  splits[1];
                        RecevoirMessage(instance, new Message("Sever","User " + oldName + " is now know as " + splits[1],-1));
                    }
                }
                catch (ArrayIndexOutOfBoundsException e)
                {
                    System.err.println("Not enough parameters");
                    instance.SendMessage(new Message("Server","Not enough parameters",-1));
                }
            }

            // Envoyer le message à tout le monde
            else {
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
            // Si le message est vide, c'est une requette d'ID de la part du client. On lui fournit sa nouvelle ID
            if (msg.user == null && msg.ID == -1)
            {
                instance.SendMessage(new Message(null,"/setID",userIDCount++));
                System.err.println("New id affected");
            }
            else if (msg.ID != -2)
            {
                UserList.put(msg.ID,msg.user);
                instance.Name = msg.user;
                System.err.println("User " + msg.user + " is connected");
                Message connexionMessage = new Message("Server","User " + msg.user + " is connected", -1);
                RecevoirMessage(null, connexionMessage);
            }

        }

    }

    @Override
    public void Disconnect(SocketThread instance, Thread thread) {
        UserList.remove(instance.Name);
        Message connexionMessage = new Message("Server","User " + instance.Name + " is disconnected", -1);
        System.err.println(connexionMessage);
        RecevoirMessage(null, connexionMessage);

        ChildServers.remove(instance);
        ChildThreads.remove(thread);
    }
}
