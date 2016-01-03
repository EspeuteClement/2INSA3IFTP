package messagerie.client;

import messagerie.protocol.Message;
import messagerie.threads.MessagerieInterface;
import messagerie.threads.ThreadableSocket;

import java.io.IOException;
import java.net.Socket;
import java.util.concurrent.CopyOnWriteArrayList;

/** A Client that can exchange messages with a remote server. Need to be hosted in a interface to be useful
 * Created by element on 18/12/15.
 */
public class MessagerieClient implements MessagerieInterface {
    Socket ServerSocket = null;

    ThreadableSocket ConnexionServeur = null;
    Thread ConnexionThread = null;


    int ID = -1;

    private MessagerieInterface host;

    protected CopyOnWriteArrayList<Message> MessageHistory = new CopyOnWriteArrayList<Message>();

    boolean connected = true;

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
        ConnexionServeur.SendMessage(new Message(null,null,Message.USER_LOGIN_MSG));
    }



    public void EnvoyerMessage(String msg) {
        ConnexionServeur.SendMessage(new Message(null,msg, ID));
    }

    @Override
    public synchronized void RecevoirMessage(ThreadableSocket instance, Message msg) {
        if (msg.message != null)
        {
            // Message d'affectation d'une ID au client par le serveur
            if (msg.message.equals("/setID"))
            {
                this.ID = msg.ID;
                ConnexionServeur.ID = msg.ID;
                // Envoyer le message d'affectation du nouveau nom
                instance.SendMessage(new Message("NewUser",null,ID));
            }
            else
            {
                MessageHistory.add(msg);
                host.RecevoirMessage(instance,msg);
            }
        }


    }

    @Override
    public void Disconnect(ThreadableSocket instance, Thread thread) {
        host.Disconnect(instance,thread);
        connected = false;
    }
}
