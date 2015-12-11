package tpmessagerie.protocol;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;

public interface MessagerieServeurITF extends Remote {
	/** Envoie un méssage sur le serveur
	 * @param leMessage Le message à envoyer
	 * @return 1 si le message est bien arrivé
	 * @throws RemoteException
	 */
    void envoyerMsgServeur(Message leMessage) throws RemoteException;
    
    /** Enregistre un client sur le serveur
     * @param leClient le client à enregistrer
     * @return TODO
     * @throws RemoteException
     */
    boolean enregistrerClient(MessagerieClientITF leClient) throws RemoteException;
    
    /** Supprime le client du serveur
     * @param leClient le client à supprimer
     * @throws RemoteException
     */
    void supprimerClient(MessagerieClientITF leClient) throws RemoteException;
    
    ArrayList<Message> recupererHistorique() throws RemoteException;
}
