package tpmessagerie.client;

import tpmessagerie.protocol.Message;

import javax.swing.*;
import javax.swing.text.BadLocationException;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by element on 13/12/15.
 */

public class ClientGuiWindow extends JFrame {
    private JPanel theJPanel;
    private JButton sendButton;
    private JTextField message;
    private JList userList;
    private JTextPane textPane1;
    private JTextArea chatHistory;

    private StyledDocument MessageDisplayContent;

    public synchronized void setChatText(String text)
    {
        SimpleAttributeSet style = new SimpleAttributeSet();

        try {
            MessageDisplayContent.insertString(MessageDisplayContent.getLength(),"\n"+text,style);
        } catch (BadLocationException e) {
            e.printStackTrace();
        }
    }



    Client client;
    Thread clientThread;
    int positionInHistory = 0;

    public ClientGuiWindow(){
        setSize(400,400);
        setMinimumSize(new Dimension(250,250));
        setContentPane(theJPanel);
        client = new Client(this);
        clientThread = new Thread(client);
        clientThread.start();



        sendButton.addActionListener(
                new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent actionEvent) {
                        String content = message.getText();
                        client.EnvoyerMsg(new Message("Bob",content));

                    }
                }
        );
        MessageDisplayContent = textPane1.getStyledDocument();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

    }

    public static void main(String[] args)
    {
        ClientGuiWindow c = new ClientGuiWindow();

    }
}