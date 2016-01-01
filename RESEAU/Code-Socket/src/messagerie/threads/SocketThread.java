package messagerie.threads;

import messagerie.protocol.Message;

import java.io.*;
import java.net.Socket;

/**
 * Created by element on 18/12/15.
 */
public class SocketThread implements Runnable {
    MessagerieInterface Mother = null;
    public String Name = null;
    ObjectInputStream InStream = null;

    Socket ClientSocket = null;
    ObjectOutputStream OutStream = null;

    Boolean Connected = false;

    public SocketThread(MessagerieInterface mother, Socket cs) throws java.io.IOException{
        Mother = mother;
        ClientSocket = cs;
        OutStream = new ObjectOutputStream(ClientSocket.getOutputStream());
        Message dummymessage = new Message(null,null, -2);
        OutStream.writeObject(dummymessage);
        InStream = new ObjectInputStream(ClientSocket.getInputStream());
        Connected = true;

    }

    @Override
    public void run() {
        try
        {
            waitForMessages();
        }
        catch (Exception e)
        {

        }

    }

    public void waitForMessages()
    {
        while (Connected)
        {
            try{
                Message line = (Message) InStream.readObject();
                if (line == null)
                {
                    break;
                }
                if (true)
                {
                    Mother.RecevoirMessage(this, line);
                }
            }
            catch (Exception e)
            {
                System.err.println("Error, the distant socket client is dead !");
                e.printStackTrace();
                Connected = false;
                Mother.Disconnect(this,Thread.currentThread());
                break;
            }
        }
    }

    public synchronized void SendMessage(Message msg)
    {
        try {
            if (Connected)
            {
                OutStream.writeObject(msg);
                System.err.println("  SocketThread : Sent message " + msg.toString());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
