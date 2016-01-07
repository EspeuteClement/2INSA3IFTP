package messagerie.client;

import messagerie.protocol.Message;
import messagerie.protocol.MessagerieInterface;
import messagerie.threads.ThreadableSocket;

import java.io.IOException;
import java.net.Socket;
import java.util.concurrent.CopyOnWriteArrayList;

/** A Client that can exchange messages with a remote server. Need to be hosted in a interface to be useful
 * Created by element on 18/12/15.
 */
public class MessagerieClient implements MessagerieInterface {


    /**Create a MessagerieClient.
     *
     * @param adress The adress of the remote server
     * @param port The port where the remote server is connected
     * @param host The MessagerieInstance that host this MessagerieClient
     * @throws IOException
     */
    public MessagerieClient(String adress, int port, MessagerieInterface host) throws IOException
    {
        this.host = host;
        MessageHistory = new CopyOnWriteArrayList<Message>();
        ServerSocket = new Socket(adress,port);
        ConnexionServeur = new ThreadableSocket(this,ServerSocket);
        ConnexionThread = new Thread(ConnexionServeur);
        ConnexionThread.start();
    }

    /** Send a Message msg to the remote server
     *
     * @param msg the messageto send
     */
    public void EnvoyerMessage(String msg) {
        ConnexionServeur.SendMessage(new Message(null,msg, ID));
    }

    @Override
    public synchronized void RecevoirMessage(ThreadableSocket instance, Message msg) {
        if (msg.message != null)
        {
                MessageHistory.add(msg);
                host.RecevoirMessage(instance,msg);
        }


    }

    @Override
    public void Disconnect(ThreadableSocket instance, Thread thread) {
        host.Disconnect(instance,thread);
        connected = false;
    }




    int ID = -1;

    private MessagerieInterface host;
    protected CopyOnWriteArrayList<Message> MessageHistory = new CopyOnWriteArrayList<Message>();
    boolean connected = true;
    private Socket ServerSocket = null;
    private ThreadableSocket ConnexionServeur = null;
    private Thread ConnexionThread = null;

}
