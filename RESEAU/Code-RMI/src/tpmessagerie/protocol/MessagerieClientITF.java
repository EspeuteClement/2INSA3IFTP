package tpmessagerie.protocol;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface MessagerieClientITF extends Remote {
	/** Envoie un méssage sur le serveur
	 * @param leMessage Le message à envoyer
	 * @return 1 si le message est bien arrivé
	 * @throws RemoteException
	 */
    void envoyerMsgClient(Message leMessage) throws RemoteException;
    
}
