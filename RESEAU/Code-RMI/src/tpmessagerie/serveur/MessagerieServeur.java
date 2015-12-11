package tpmessagerie.serveur;

import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.LinkedHashSet;

import tpmessagerie.protocol.Message;
import tpmessagerie.protocol.MessagerieClientITF;
import tpmessagerie.protocol.MessagerieServeurITF;

public class MessagerieServeur implements MessagerieServeurITF {
	
	public MessagerieServeur()
	{
		listeMessages = new ArrayList<Message>(0);
		listeClients = new LinkedHashSet<MessagerieClientITF>(0);
	}
	
	@Override
	public void envoyerMsgServeur(Message leMessage) throws RemoteException {
		listeMessages.add(leMessage);
		for (MessagerieClientITF client : listeClients )
		{
			try{
				client.envoyerMsgClient(leMessage);
			}
			catch (RemoteException e)
			{
				System.err.println("Un message n'a pas pu être envoyé au client");
				e.printStackTrace();
			}
			
		}
		System.out.println(leMessage.utilisateur + " : " + leMessage.contenu);
	}
	
	
	private ArrayList<Message> listeMessages;


	@Override
	public boolean enregistrerClient(MessagerieClientITF leClient) throws RemoteException {
		if (!listeClients.contains(leClient))
		{
			listeClients.add(leClient);
			return true;
		}
		return false;
	}

	@Override
	public void supprimerClient(MessagerieClientITF leClient) throws RemoteException {
		listeClients.remove(leClient);
	}
	
	LinkedHashSet<MessagerieClientITF> listeClients;


	@Override
	public ArrayList<Message> recupererHistorique() throws RemoteException {
		return listeMessages;
	}
}
