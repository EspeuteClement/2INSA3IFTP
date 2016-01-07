package messagerie.protocol;

import messagerie.protocol.Message;
import messagerie.threads.ThreadableSocket;

/** Interface que doivent implémenter les classes qui souhaitent communiquer avec
 * un ThreadableSocket.
 * Created by element on 18/12/15.
 */
public interface MessagerieInterface {

    /** Called when the ThreadableSocket recives a message msg.
     *
     * @param instance The ThreadableSocket that received the message
     * @param msg The received message
     */
    void RecevoirMessage(ThreadableSocket instance, Message msg);

    /** Called when the remote Interface is disconected
     *
     * @param instance
     * @param thread
     */
    void Disconnect(ThreadableSocket instance, Thread thread);


}
