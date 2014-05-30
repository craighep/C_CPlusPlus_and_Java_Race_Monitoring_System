
import java.io.IOException;
import uk.ac.aber.dcs.crh13.fileio.FileIO;
import uk.ac.aber.dcs.crh13.frame.Gui;

/**
 * Runnable class used to launch checkpoint manager program. Contains name
 * output of program and calls methods for getting files containing required
 * information, and calls graphical side of system to open.
 *
 * @author craig
 */
public class runnable {

    private static String[] entrants;
    private static int[] checkPoints;
    private static String[] courses;
    private static String fileName;

    public static void main(String[] args) throws IOException {
        System.out.println("   ___ _               _                _       _");
        System.out.println("  / __\\ |__   ___  ___| | ___ __   ___ (_)_ __ | |_");
        System.out.println(" / /  | '_ \\ / _ \\/ __| |/ / '_ \\ / _ \\| | '_ \\| __|");
        System.out.println("/ /___| | | |  __/ (__|   <| |_) | (_) | | | | | |_ ");
        System.out.println("\\____/|_| |_|\\___|\\___|_|\\_\\ .__/ \\___/|_|_| |_|\\__|");
        System.out.println("                           |_|                      ");

        System.out.println("  /\\/\\   __ _ _ __   __ _  __ _  ___ _ __ ");
        System.out.println(" /    \\ / _` | '_ \\ / _` |/ _` |/ _ \\ '__|");
        System.out.println("/ /\\/\\ \\ (_| | | | | (_| | (_| |  __/ | ");
        System.out.println("\\/    \\/\\__,_|_| |_|\\__,_|\\__, |\\___|_| ");
        System.out.println("                          |___/  ");
        System.out.println("(crh13)\n");


        FileIO fio = new FileIO();
        entrants = fio.get_entrants();
        checkPoints = fio.get_checkpoints();
        courses = fio.get_courses();
        fileName = fio.get_current_checktimes();

        Gui gui = new Gui();
        gui.createAndShowGUI(entrants, checkPoints, courses, fileName);


    }
}
