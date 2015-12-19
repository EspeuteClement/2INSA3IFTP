package messagerie.threads;

import messagerie.protocol.Message;

/**
 * Created by element on 18/12/15.
 */
public interface MessagerieInterface {
    void RecevoirMessage(SocketThread instance, Message msg);

    void Disconnect(SocketThread instance, Thread thread);
}
