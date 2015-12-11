package tpmessagerie.client;

import java.rmi.RemoteException;

import java.util.ArrayList;

import tpmessagerie.protocol.Message;
import tpmessagerie.protocol.MessagerieClientITF;

public class MessagerieClient implements MessagerieClientITF {
	
	public MessagerieClient()
	{
		listeMessages = new ArrayList<Message>(0);
	}
	
	
	@Override
	public void envoyerMsgClient(Message leMessage) throws RemoteException {
		listeMessages.add(leMessage);
		System.out.println(leMessage.utilisateur + " : " + leMessage.contenu);
	}
	
	ArrayList<Message> listeMessages;

}
