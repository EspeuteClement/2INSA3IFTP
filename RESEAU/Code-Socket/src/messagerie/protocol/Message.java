package messagerie.protocol;

import java.io.Serializable;

/** Simple struct containing the data in a message
 * Created by element on 18/12/15.
 */
public class Message implements Serializable{
    private static final long serialVersionUID = 666666667L;

    public String user;     // The name of the user in the message
    public String message;  // The content of the message
    public int ID;          // The ID of the message sender

    public Message ()
    {

    }

    public Message(String u, String m, int id)
    {
        user = u;
        message = m;
        ID = id;
    }

    public String toString()
    {
        return user + " : " + message;
    }

    /* These are the values that ID takes when non user message are sent.
     */
    public final static int SERVER_MSG = -1;
    public final static int SERVER_ERR_MSG = -2;
    public final static int SERVER_WHISPER_MSG = -3;

    /**Used when the user don't have an assigned ID yet*/
    public final static int USER_LOGIN_MSG = -100;

}
