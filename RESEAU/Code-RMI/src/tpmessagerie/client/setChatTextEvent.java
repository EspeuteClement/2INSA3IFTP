package tpmessagerie.client;

import tpmessagerie.protocol.Message;

import javax.swing.*;

/**
 * Created by element on 13/12/15.
 */
public class setChatTextEvent implements Runnable {
    JTextArea oktamer;
    String message;
    public setChatTextEvent(JTextArea g, String m)
    {
        oktamer = g;
        message = m;
    }

    public void run()
    {
        oktamer.setText(message);
    }
}
