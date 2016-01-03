package messagerie.client;

import messagerie.protocol.Message;
import messagerie.threads.MessagerieInterface;
import messagerie.threads.ThreadableSocket;

import javax.swing.*;
import javax.swing.text.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * Created by element on 29/12/15.
 */
public class ClientGui extends JFrame implements MessagerieInterface {
    private JTextField MessageField;
    private JButton SendButton;
    private JTextPane MessageDisplay;
    private StyledDocument MessageDisplayContent;

    private JList UserDisplay;
    protected CopyOnWriteArrayList<String> UserList = new CopyOnWriteArrayList<>();

    private JPanel ChatFrame;


    private MessagerieClient Client;

    /** Constructeur de ClientGui. Renvoie un méssage d'erreur si le serveur distant
     *  n'a pas pu être joint.
     * @param adress L'adresse du serveur à joindre
     * @param port Le port du serveur à joindre
     */
    public ClientGui(String adress, int port)
    {

        try {
            // TODO : Delay the creation of the MessagerieClient
            ImageIcon icon = new ImageIcon("src/res/catIcon1.png");
            this.setIconImage(icon.getImage());

            // Set the name of the app
            this.setName("Le Chat");
            this.setTitle("Le Chat");

            // Set the chat-box to autoscroll
            DefaultCaret caret = (DefaultCaret)MessageDisplay.getCaret();
            caret.setUpdatePolicy(DefaultCaret.ALWAYS_UPDATE);

            MessageDisplayContent = MessageDisplay.getStyledDocument();

            // Create the client
            Client = new MessagerieClient(adress,port,this);

            // Create the action lisntener that wil send the message, and asign it to the button and text field
            ActionListener sendMsg = new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent actionEvent) {
                    if(MessageField.getText().length() > 0) {
                        Client.EnvoyerMessage(MessageField.getText());
                        MessageField.setText("");
                    }
                }
            };

            SendButton.addActionListener(sendMsg);
            MessageField.addActionListener(sendMsg);



            /* Double click sur la liste d'utilisateurs pour automatiquement envoyer un message privé */
            UserDisplay.addMouseListener(new MouseAdapter() {
                public void mouseClicked(MouseEvent evt) {
                    JList list = (JList)evt.getSource();
                    if (evt.getClickCount() == 2) {

                        // Double-click detected
                        int index = list.locationToIndex(evt.getPoint());
                        MessageField.setText("/w "+list.getModel().getElementAt(index)+" ");
                        MessageField.requestFocus();
                    }
                }
            });


            // Set the default sizes of the window
            setSize(400,400);
            setMinimumSize(new Dimension(250,250));

            // Draw the window
            setContentPane(ChatFrame);
            setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            setVisible(true);
        } catch (IOException e) {
            System.err.println("Error, couldn't connect to distant server " + adress + ":" + port);
            e.printStackTrace();
        }

    }

    /** Main method. Simply create the window.
     * @param args
     */
    public static void main(String args[])
    {
        ClientGui c = new ClientGui(args[0],Integer.parseInt(args[1]));
    }

    @Override
    public synchronized void RecevoirMessage(ThreadableSocket instance, Message msg) {
        try {
            SimpleAttributeSet style = new SimpleAttributeSet();
            if (msg.ID < 0 ) //Special message
            {
                // If the message is a command message
                if (msg.message.charAt(0) == '/') {
                    String[] splits = msg.message.split("\\s+");
                    if (splits[0].equals("/UserList"))
                    {
                        String array[] = new String[splits.length-1];
                        for (int i = 1; i<splits.length;i++)
                        {
                            array[i-1] = splits[i];
                        }
                        UserDisplay.setListData(array);
                        return;
                    }
                }

                StyleConstants.setItalic(style,true);
                StyleConstants.setForeground(style,Color.LIGHT_GRAY);
                if (msg.ID == Message.SERVER_ERR_MSG) //Error Msg
                {
                    StyleConstants.setForeground(style,Color.RED);
                }
                if (msg.ID == Message.SERVER_WHISPER_MSG) //Whisper Msg
                {
                    StyleConstants.setForeground(style,Color.DARK_GRAY);
                }
            }
            MessageDisplayContent.insertString(MessageDisplayContent.getLength(),"\n"+msg.toString(),style);


        } catch (BadLocationException e) {
            e.printStackTrace();
        } catch (NullPointerException e)
        {
            e.printStackTrace();
            System.err.println(msg);
            System.err.println(MessageDisplayContent);
        }
    }

    @Override
    public void Disconnect(ThreadableSocket instance, Thread thread) {
        RecevoirMessage(instance, new Message("Server","Error, Distant server is disconnected",-2));
    }
}
