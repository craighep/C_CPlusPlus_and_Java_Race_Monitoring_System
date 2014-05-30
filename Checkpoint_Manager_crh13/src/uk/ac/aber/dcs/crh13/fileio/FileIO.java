package uk.ac.aber.dcs.crh13.fileio;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.channels.FileLock;
import java.nio.channels.OverlappingFileLockException;

/**
 * Class responsible for reading in current text files (nodes, entrants, check-
 * point files to be updated). Called at start of program to be ready loaded for
 * gui implementation.
 *
 * @author Craig Heptinstall
 */
public class FileIO {

    private String[] entrants = new String[30];
    private int[] checkPoints = new int[30];
    private static String[] course = new String[30];

    /**
     * Method for reading and getting current entrants within created event.
     *
     * @param void
     */
    public String[] get_entrants() {
        boolean check = false;

        while (check == false) {
            System.out.println("Please Input Entrants File Name:");
            InputStreamReader converter = new InputStreamReader(System.in);
            BufferedReader in = new BufferedReader(converter);
            try {
                // make a 'file' object   
                File file = new File(in.readLine());
                //  Get data from this file using a file reader.   
                FileReader fr = new FileReader(file);
                // To store the contents read via File Reader  
                BufferedReader br = new BufferedReader(fr);
                // Read br and store a line in 'data', print data  
                String data;

                int i = 0;
                while ((data = br.readLine()) != null) {
                    entrants[i] = data;
                    i++;
                    check = true;
                }
            } catch (IOException e) {
                System.out.println("No or Incorrect File Inputted\n");
                check = false;
            }

        }
        return entrants;

    }

    /**
     * Method for getting nodes on each course. This will be later used for when
     * selecting the nodes the entrant has got to.
     */
    public int[] get_checkpoints() {
        boolean check = false;

        while (check == false) {
            System.out.println("\nPlease Input Nodes File Name:");
            InputStreamReader converter = new InputStreamReader(System.in);
            BufferedReader in = new BufferedReader(converter);
            try {
                // make a 'file' object   
                File file = new File(in.readLine());
                //  Get data from this file using a file reader.   
                FileReader fr = new FileReader(file);
                // To store the contents read via File Reader  
                BufferedReader br = new BufferedReader(fr);
                // Read br and store a line in 'data', print data  
                String data;
                int i = 0;
                while ((data = br.readLine()) != null) {
                    String[] parts = data.split(" ");
                    if ("CP".equals(parts[1])) {
                        checkPoints[i] = Integer.parseInt(parts[0]);
                    }
                    i++;
                }
                return checkPoints;

            } catch (IOException e) {
                System.out.println("No or Incorrect File Inputted\n");
                check = false;
            }
        }
        return null;


    }

    /**
     * Method for getting nodes on each course. This will be later used for when
     * selecting the nodes the entrant has got to.
     */
    public String[] get_courses() {
        boolean check = false;

        while (check == false) {
            System.out.println("\nPlease Input Courses File Name:");
            InputStreamReader converter = new InputStreamReader(System.in);
            BufferedReader in = new BufferedReader(converter);
            try {
                // make a 'file' object   
                File file = new File(in.readLine());
                //  Get data from this file using a file reader.   
                FileReader fr = new FileReader(file);
                // To store the contents read via File Reader  
                BufferedReader br = new BufferedReader(fr);
                // Read br and store a line in 'data', print data  
                String data;

                int i = 0;
                while ((data = br.readLine()) != null) {
                    course[i] = data;
                    i++;
                    check = true;
                }
            } catch (IOException e) {
                System.out.println("No or Incorrect File Inputted\n");
                check = false;
            }

        }
        return course;

    }

    /**
     * Method for reading and getting current entrants check point times so that
     * the user cannot select times in the past. This file will be appended to
     * when writing check point times to.
     *
     * @param void
     */
    public String get_current_checktimes() throws FileNotFoundException, IOException {
        boolean check = false;
        String fileName = null;
        while (check != true) {
            System.out.println("\nPlease Input The Checkpoint Times File Name You Want To Update:");
            InputStreamReader converter = new InputStreamReader(System.in);
            BufferedReader in = new BufferedReader(converter);
            fileName = in.readLine();
            check = true;
            try {
                File file = new File(fileName);

                FileChannel channel = new RandomAccessFile(file, "rw").getChannel();

                FileLock lock = null;
                try {
                    lock = channel.tryLock();
                } catch (OverlappingFileLockException e) {
                    check = false;
                    System.out.println("The File Is Currently Locked Try Again Later");
                }



            } catch (Exception e) {
            }
        }


        return fileName;
    }
}
