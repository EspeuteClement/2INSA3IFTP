package messagerie.threads;

import messagerie.protocol.Message;

/** Interface que doivent implémenter les classes qui souhaitent communiquer avec
 * un ThreadableSocket.
 * Created by element on 18/12/15.
 */
public interface MessagerieInterface {

    /** Méthode appelée lorsque le ThreadableSocket instance recoit un message.
     *
     * @param instance L'instance qui a reçu le méssage
     * @param msg Le méssage reçu
     */
    void RecevoirMessage(ThreadableSocket instance, Message msg);

    /**
     * Méthode appelée lorsque le ThreadableSocket distant avec qui instance communiquait s'est
     * déconnecté.
     * @param instance
     * @param thread
     */
    void Disconnect(ThreadableSocket instance, Thread thread);


}
