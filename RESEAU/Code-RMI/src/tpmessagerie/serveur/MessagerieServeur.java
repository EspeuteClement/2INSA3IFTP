package tpmessagerie.serveur;

import java.rmi.RemoteException;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;
import java.util.concurrent.CopyOnWriteArrayList;

import tpmessagerie.protocol.Message;
import tpmessagerie.protocol.MessagerieClientITF;
import tpmessagerie.protocol.MessagerieServeurITF;

public class MessagerieServeur implements MessagerieServeurITF {
	
	public MessagerieServeur()
	{

	}
	
	@Override
	public void envoyerMsgServeur(Message leMessage) throws RemoteException {
		listeMessages.add(leMessage);
		for (MessagerieClientITF client : listeClients.keySet() )
		{
			try{
				client.envoyerMsgClient(leMessage);
			}
			catch (RemoteException e)
			{
				System.err.println("Un message n'a pas pu être envoyé au client");
				listeClients.remove(client);
				//e.printStackTrace();
			}
			
		}
		System.out.println(leMessage.utilisateur + " : " + leMessage.contenu);
	}
	
	
	private CopyOnWriteArrayList<Message> listeMessages = new CopyOnWriteArrayList<>();


	@Override
	public boolean enregistrerClient(MessagerieClientITF leClient) throws RemoteException {
		if (!listeClients.contains(leClient))
		{
			listeClients.put(leClient,0);
			return true;
		}
		return false;
	}

	@Override
	public void supprimerClient(MessagerieClientITF leClient) throws RemoteException {
		listeClients.remove(leClient);
	}
	
	ConcurrentHashMap<MessagerieClientITF,Integer> listeClients = new ConcurrentHashMap<>();


	@Override
	public CopyOnWriteArrayList<Message> recupererHistorique() throws RemoteException {
		return listeMessages;
	}
}
