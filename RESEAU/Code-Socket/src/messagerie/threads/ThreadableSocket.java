package messagerie.threads;

import messagerie.protocol.Message;

import java.io.*;
import java.net.Socket;

/** Classe permettant de faire tourner un socket dans un thread.
 * Le thread attends en boucle l'arrivée d'un méssage, et permets d'en envoyer
 * Created by element on 18/12/15.
 */
public class ThreadableSocket implements Runnable {

    /**
     *  Constructeur de la classe.
     *
     * @param mother L'objet auquel ce socket thread est rattaché
     * @param cs Le socket (qui doit déjà être connecté à un autre socket) qui servira à la discussion.
     * @throws java.io.IOException
     */
    public ThreadableSocket(MessagerieInterface mother, Socket cs) throws java.io.IOException{
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

    /**
     * Boucle infinie qui attends la reception d'un méssage provenant du socket distant
     * Appelle RecevoirMessage de Mother à chaque fois qu'un méssage est reçu, ou
     * Appelle Disconnect de Mother quand le socket distant s'est déconnecté.
     */
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
                //e.printStackTrace();
                Connected = false;
                Mother.Disconnect(this,Thread.currentThread());
                break;
            }
        }
    }

    /**
     * Envoie le méssage msg au socket distant.
     * @param msg le méssage à envoyer
     */
    public synchronized void SendMessage(Message msg)
    {
        try {
            if (Connected)
            {
                OutStream.writeObject(msg);
                System.err.println("  ThreadableSocket : Sent message " + msg.toString());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Atributs
    MessagerieInterface Mother = null; // L'objet qui possède ce ThreadableSocket
    public int ID = -1;
    ObjectInputStream InStream = null;

    Socket ClientSocket = null;
    ObjectOutputStream OutStream = null;

    Boolean Connected = false;
}
