package messagerie.protocol;

import java.io.Serializable;

/**
 * Created by element on 18/12/15.
 */
public class Message implements Serializable{
    private static final long serialVersionUID = 666666667L;
    public String user;
    public String message;

    public Message (String u, String m)
    {
        user = u;
        message = m;
    }

    public String toString()
    {
        return user + " : " + message;
    }
}
