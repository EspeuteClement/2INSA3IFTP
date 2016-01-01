package messagerie.client;

import messagerie.protocol.Message;
import messagerie.threads.MessagerieInterface;
import messagerie.threads.SocketThread;

import javax.swing.*;
import javax.swing.text.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

/**
 * Created by element on 29/12/15.
 */
public class ClientGui extends JFrame implements MessagerieInterface {
    private JTextField MessageFiled;
    private JButton SendButton;
    private JTextPane MessageDisplay;
    private StyledDocument MessageDisplayContent;

    private JList UserDisplay;
    private JPanel ChatFrame;


    private MessagerieClient Client;

    public ClientGui(String adress, int port)
    {

        try {
            // TODO : Delay the creation of the MessagerieClient
            ImageIcon icon = new ImageIcon("src/res/catIcon1.png");
            this.setIconImage(icon.getImage());
            this.setName("Mundane Cat");
            this.setTitle("Mundane Cat");
            DefaultCaret caret = (DefaultCaret)MessageDisplay.getCaret();
            caret.setUpdatePolicy(DefaultCaret.ALWAYS_UPDATE);

            MessageDisplayContent = MessageDisplay.getStyledDocument();

            Client = new MessagerieClient(adress,port,this);

            ActionListener sendMsg = new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent actionEvent) {
                    if(MessageFiled.getText().length() > 0) {
                        Client.EnvoyerMessage(MessageFiled.getText());
                        MessageFiled.setText("");
                    }
                }
            };

            SendButton.addActionListener(sendMsg);
            MessageFiled.addActionListener(sendMsg);

            setSize(400,400);
            setMinimumSize(new Dimension(250,250));
            setContentPane(ChatFrame);
            setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            setVisible(true);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public static void main(String args[])
    {
        ClientGui c = new ClientGui(args[0],Integer.parseInt(args[1]));
    }

    @Override
    public synchronized void RecevoirMessage(SocketThread instance, Message msg) {
        try {
            SimpleAttributeSet style = new SimpleAttributeSet();
            if (msg.ID == -1 ) //Server message
            {
                StyleConstants.setItalic(style,true);
                StyleConstants.setForeground(style,Color.LIGHT_GRAY);

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
    public void Disconnect(SocketThread instance, Thread thread) {

    }
}
