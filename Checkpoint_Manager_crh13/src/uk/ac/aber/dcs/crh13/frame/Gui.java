package uk.ac.aber.dcs.crh13.frame;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.channels.FileLock;
import javax.swing.*;
import uk.ac.aber.dcs.crh13.panel.Panel;

/**
 * Class required to open new JFrame GUI for checkpoint manager.
 *
 * @author craig
 */
public class Gui {

    private static String FileName;

    /**
     * Creates JFrame window, then adds in the panel constructed in the panel
     * class.
     *
     * @param void
     */
    public void createAndShowGUI(String[] entrants, int[] checkPoints, String[] courses, String fileName) {
        FileName = fileName;
        JFrame frame = new JFrame("Checkpoint Manager");

        //Create and set up the content pane.
        Panel myPanel = new Panel();
        frame.setContentPane(myPanel.createContentPane(entrants, checkPoints, courses, fileName));

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(320, 350);
        frame.setVisible(true);
        frame.setLocationRelativeTo(null);

        frame.addWindowListener(new WindowExitAdapter());
    }

    private class WindowExitAdapter extends WindowAdapter {

        @Override
        public void windowClosing(WindowEvent e) {
            try {
                // Get a file channel for the file
                File file = new File(FileName);
                FileChannel channel = new RandomAccessFile(file, "rw").getChannel();

                FileLock lock = channel.lock();

                // Release the lock
                lock.release();

                // Close the file
                channel.close();
            } catch (Exception ex) {
            }

        } //end of WindowExitAdapter class
    }
}