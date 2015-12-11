package tpmessagerie.client;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Scanner;

import tpmessagerie.protocol.Message;
import tpmessagerie.protocol.MessagerieClientITF;
import tpmessagerie.protocol.MessagerieServeurITF;

public class Client {
	public static void main(String[] args) {

        String host = (args.length < 1) ? null : args[0];
        String nom = (args.length < 2) ? "Bob" : args[1];
        int idDernierMessage = 0;
        try {
            Registry registry = LocateRegistry.getRegistry(host);
            MessagerieServeurITF messagerieServeur = (MessagerieServeurITF) registry.lookup("Messagerie");
            
            MessagerieClient messagerieClient = new MessagerieClient();
            
            MessagerieClientITF stub = (MessagerieClientITF) UnicastRemoteObject.exportObject(messagerieClient,0);
            messagerieServeur.enregistrerClient(stub);
            
            ArrayList<Message> historique = messagerieServeur.recupererHistorique();
            for (Message m : historique)
            {
            	System.out.println(m);
            }
            
            Scanner in = new Scanner(System.in);
           
            while (true)
            {
            	String message = in.nextLine();
            	Message m = new Message(nom,message);
            	messagerieServeur.envoyerMsgServeur(m);
            }
            
            
        } catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }
    }
	
	
	
}
