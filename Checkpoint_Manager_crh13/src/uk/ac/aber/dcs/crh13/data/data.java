package uk.ac.aber.dcs.crh13.data;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

/**
 * Class responsible for writing checkpoint information to checkpoint file. Uses
 * information sent from GUI and filename from FileIO class to check if an
 * entrant was expected at a checkpoint and then write to file accordingly.
 *
 * @author craig
 */
public class data {

    /**
     * Method for writing checkpoint update to file, and calling the
     * checkExpected method in order to check if an entrant went to an
     * appropriate checkpoint.
     */
    public boolean addUpdate(String cpType, String entrant, int node, String time, String[] courses, String fileName) {

        String EntrantCourse[] = entrant.split(" "); //  split up the entrant string to get specific parts
        boolean check = checkExpected(courses, EntrantCourse[1], node);
        if (check == false) { // check if the entrant was not expected at the checkpoint
            cpType = "I";
        }
        try {
            try (PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(fileName, true)))) {
                out.println(cpType + " " + node + " " + EntrantCourse[0] + " " + time);
            }
        } catch (IOException e) {
            System.out.println("Could Not write");
        }
        if (check == false) {
            return false; // return to paneel to inform that the entrant went to an inappropriate checkpoint for alert
        }
        return true;
    }

    /**
     * Method for checking if the entrants checkpoint is registered on their
     * course. Returns true if the checkpoint exists on the entrants course,
     * false if not. Does this by looping through the entrants designated
     * course, then checks for a match.
     */
    public boolean checkExpected(String[] courses, String EntrantCourse, int node) {
        boolean check = false;
        for (int i = 0; i < courses.length; i++) {
            if (courses[i] != null) {
                String[] parts = courses[i].split(" ");
                if (EntrantCourse.equals(parts[0])) { // get course entrant is registered for
                    for (int a = 1; a < parts.length; a++) {

                        if (Integer.parseInt(parts[a]) == node) { // check every checkpoint on the course
                            check = true;
                        }

                    }
                }
            }
        }
        return check;

    }
}