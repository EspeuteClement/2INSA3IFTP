package tpmessagerie.client;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ClientGui extends JDialog implements Runnable {
    private JPanel contentPane;
    private JButton Send;
    private JTextField Message;
    private JList ListeUtilisateurs;
    private JTextArea chat;

    public ClientGui() {
        setContentPane(contentPane);
        setModal(true);
        getRootPane().setDefaultButton(Send);

        Send.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onOK();
            }
        });
    }

    public void setChatText(String text)
    {
        chat.setText(text);
        chat.validate();
    }

    private void onOK() {
// add your code here
    }

    public void run()
    {
        ClientGui dialog = new ClientGui();
        dialog.setMinimumSize(new Dimension(400, 400));
        dialog.setChatText("This is a test string \nI like trains");
        dialog.pack();
        dialog.setVisible(true);

        //System.exit(0);
    }

    public static void main(String[] args) {
        ClientGui dialog = new ClientGui();
        dialog.setMinimumSize(new Dimension(400, 400));
        //dialog.setChatText("This is a test string \nI like trains");
        //Client c = new Client(dialog);
        //Thread cThread = new Thread(c);
        //cThread.start();
        dialog.pack();
        dialog.setVisible(true);
    }
}
