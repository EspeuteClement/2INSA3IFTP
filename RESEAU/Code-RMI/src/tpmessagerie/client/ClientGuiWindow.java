package tpmessagerie.client;

import tpmessagerie.protocol.Message;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by element on 13/12/15.
 */
public class ClientGuiWindow extends JFrame {
    private JPanel test;
    private JButton sendButton;
    private JTextField message;
    private JList userList;
    private JTextArea chatHistory;

    public void setChatText(String text)
    {
        SwingUtilities.invokeLater(new setChatTextEvent(chatHistory,chatHistory.getText()+"\n"+text));
        //chatHistory.setText(text);
        //chatHistory.repaint();
        //setVisible(true);
    }



    Client client;
    javax.swing.Timer t;
    Thread clientThread;
    int positionInHistory = 0;

    public ClientGuiWindow(){
        setSize(400,400);
        setMinimumSize(new Dimension(250,250));
        setContentPane(test);
        message = new JTextField();
        client = new Client(this);
        clientThread = new Thread(client);
        clientThread.start();
        t = new javax.swing.Timer(100, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                if (client != null && client.historique !=null)
                {
                    while(positionInHistory < client.historique.size())
                    {
                        chatHistory.setText(chatHistory.getText()+"\n"+client.historique.get(positionInHistory));
                        positionInHistory++;
                    }
                }

            }
        });

        t.start();



        sendButton.addActionListener(
                new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent actionEvent) {
                        String fuckYou = message.getText();
                        client.EnvoyerMsg(new Message("Bob",fuckYou));

                    }
                }
        );
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

    }

    public static void main(String[] args)
    {
        ClientGuiWindow c = new ClientGuiWindow();

    }
}
