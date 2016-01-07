package tpmessagerie.client;

import java.rmi.RemoteException;

import java.util.ArrayList;

import tpmessagerie.protocol.Message;
import tpmessagerie.protocol.MessagerieClientITF;

public class MessagerieClient implements MessagerieClientITF {

	Client leClient;
	public MessagerieClient(Client c)
	{
		leClient = c;
		listeMessages = new ArrayList<Message>(0);
	}
	
	
	@Override
	public void envoyerMsgClient(Message leMessage) throws RemoteException {
		listeMessages.add(leMessage);
		leClient.RecevoirMessage(leMessage);
	}
	
	ArrayList<Message> listeMessages;

}
