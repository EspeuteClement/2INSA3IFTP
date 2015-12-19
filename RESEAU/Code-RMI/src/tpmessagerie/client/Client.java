package tpmessagerie.client;

import java.rmi.ConnectException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Scanner;

import tpmessagerie.protocol.Message;
import tpmessagerie.protocol.MessagerieClientITF;
import tpmessagerie.protocol.MessagerieServeurITF;

import javax.swing.*;

public class Client implements Runnable{
    public void ConnectToServer(String host) throws Exception{
        Registry registry = LocateRegistry.getRegistry(host);
        messagerieServeur = (MessagerieServeurITF) registry.lookup("Messagerie");

        MessagerieClientITF stub = (MessagerieClientITF) UnicastRemoteObject.exportObject(messagerieClient,0);
        messagerieServeur.enregistrerClient(stub);

        historique = messagerieServeur.recupererHistorique();

        for (Message m : historique)
        {
            AfficherMessage(m);
        }
    }

    public Client(ClientGuiWindow theGui)
    {
        Gui = theGui;
        messagerieClient = new MessagerieClient(this);
    }

    ClientGuiWindow Gui;

    public void AfficherMessage(Message message)
    {
        //SwingUtilities.invokeLater(new setChatTextEvent(Gui.getTextArea(),message.utilisateur + " : " + message.contenu));

        System.out.println(message.utilisateur + " : " + message.contenu);
    }

    public void EnvoyerMsg(Message message)
    {
        try {
            messagerieServeur.envoyerMsgServeur(message);
        }
        catch( Exception e)
        {
            System.err.println("COULDN'T SEND MESSAGE");
        }
    }

    MessagerieClient messagerieClient;
    public ArrayList<Message> historique;
    MessagerieServeurITF messagerieServeur;

    public void run()
    {
        try{
            ConnectToServer(null);
            Scanner in = new Scanner(System.in);
            while (true)
            {
                String message = in.nextLine();
                Message m = new Message("Bob",message);
                EnvoyerMsg(m);
            }
        }
        catch (Exception e)
        {
            System.err.println("Couldn't connect");
            e.printStackTrace();
        }

    }


	public static void main(String[] args) {
        String host = (args.length < 1) ? null : args[0];
        String nom = (args.length < 2) ? "Bob" : args[1];
        int idDernierMessage = 0;
        /*Client cl = new Client();
        try {
            cl.ConnectToServer(host);
            Scanner in = new Scanner(System.in);
            ClientGui gui = new ClientGui();

            Thread Gui = new Thread(gui,"Gui");
            Gui.start();

            while (true)
            {
            	String message = in.nextLine();
            	Message m = new Message(nom,message);
            	cl.EnvoyerMsg(m);
            }



        } catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }*/
    }
	
	
	
}
