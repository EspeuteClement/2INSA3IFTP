package messagerie.server;

import messagerie.protocol.Message;
import messagerie.threads.MessagerieInterface;
import messagerie.threads.SocketThread;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * Created by element on 18/12/15.
 */
public class MotherServer implements MessagerieInterface {
    private CopyOnWriteArrayList<SocketThread> ChildServers = new CopyOnWriteArrayList<SocketThread>();
    private CopyOnWriteArrayList<Thread> ChildThreads = new CopyOnWriteArrayList<Thread>();

    private int port = 4444;
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

    public void BroadcastMessage(String msg)
    {
        for (SocketThread m : ChildServers )
        {
            m.SendMessage(msg);
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
    public void RecevoirMessage(String msg) {
        BroadcastMessage(msg);
    }
}
