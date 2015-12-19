package messagerie.client;

import messagerie.protocol.Message;
import messagerie.threads.MessagerieInterface;
import messagerie.threads.SocketThread;

import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

/**
 * Created by element on 18/12/15.
 */
public class MessagerieClient implements MessagerieInterface {
    Socket ServerSocket = null;

    SocketThread ConnexionServeur = null;
    Thread ConnexionThread = null;

    public MessagerieClient(String adress, int port) throws IOException
    {
        ServerSocket = new Socket(adress,port);
        ConnexionServeur = new SocketThread(this,ServerSocket);
        ConnexionThread = new Thread(ConnexionServeur);
        ConnexionThread.start();
    }

    public static void main(String Args[])
    {
        try
        {
            MessagerieClient Client = new MessagerieClient(Args[0],Integer.parseInt(Args[1]));

            Scanner in = new Scanner(System.in);
            while (true)
            {
                String msg = in.nextLine();
                Client.EnvoyerMessage(msg);
            }
        }
        catch (Exception e)
        {

        }

    }

    public void EnvoyerMessage(String msg) {
        ConnexionServeur.SendMessage(msg);
    }

    @Override
    public synchronized void RecevoirMessage(String msg) {
        System.out.println(msg);
    }
}
