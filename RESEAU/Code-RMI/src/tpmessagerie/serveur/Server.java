package tpmessagerie.serveur;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

import tpmessagerie.protocol.MessagerieServeurITF;

public class Server {
	public static void main(String args[]){
		try{
			MessagerieServeur laMessagerie = new MessagerieServeur();
			MessagerieServeurITF stub = (MessagerieServeurITF) UnicastRemoteObject.exportObject(laMessagerie,0);
		
			try {
				LocateRegistry.createRegistry(1099);
			}
			catch (RemoteException e)
			{
				e.printStackTrace();
			}
			Registry registry = LocateRegistry.getRegistry();
			
			registry.bind("Messagerie",stub);
			
			System.err.println("Server Ready !");
		}
		catch (Exception e){
			System.err.println("Server exception : "+e.toString());
			e.printStackTrace();
		}
	}
}
