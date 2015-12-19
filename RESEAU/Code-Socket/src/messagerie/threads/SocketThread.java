package messagerie.threads;

import messagerie.server.MotherServer;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;

/**
 * Created by element on 18/12/15.
 */
public class SocketThread implements Runnable {
    MessagerieInterface Mother = null;

    BufferedReader InputBuffer = null;

    Socket ClientSocket = null;
    PrintStream OutStream = null;

    public SocketThread(MessagerieInterface mother, Socket cs) throws java.io.IOException{
        Mother = mother;
        ClientSocket = cs;
        InputBuffer = new BufferedReader(new InputStreamReader(ClientSocket.getInputStream()));
        OutStream = new PrintStream(ClientSocket.getOutputStream());
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
        while (true)
        {
            try{
                String line = InputBuffer.readLine();
                if (line == null)
                {
                    break;
                }
                Mother.RecevoirMessage(line);
            }
            catch (Exception e)
            {
                System.err.println("Error, my client is dead !");
                break;
            }
        }
    }

    public synchronized void SendMessage(String msg)
    {
        OutStream.println(msg);
    }

}
