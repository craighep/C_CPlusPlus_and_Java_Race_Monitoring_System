package uk.ac.aber.dcs.crh13.panel;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import javax.swing.*;
import uk.ac.aber.dcs.crh13.data.data;

/**
 * Class used for implementing the panel of the user interface. Has all required
 * inputs and implements an action listener to get values. Sends these to the
 * data class that writes them to the checkpoint file.
 *
 * @author Craig
 */
public class Panel implements ActionListener {

    private JButton submit;
    private JRadioButton time = new JRadioButton();
    private JRadioButton medical = new JRadioButton();
    private JRadioButton departed = new JRadioButton();
    private JRadioButton arrived = new JRadioButton();
    private JCheckBox excluded = new JCheckBox();
    private String[] coursesArray;
    private String[] entrantArray;
    private String fileName;
    Date dateA = new Date();
    SpinnerDateModel sm = new SpinnerDateModel(dateA, null, null, Calendar.HOUR_OF_DAY);
    JSpinner timeSpinner = new JSpinner(sm);
    JComboBox entrantList = new JComboBox();
    JComboBox checkPointList = new JComboBox();

    public JPanel createContentPane(String[] entrants, int[] checkPoints, String[] courses, String fN) {
        coursesArray = courses;
        entrantArray = entrants;
        fileName = fN;

        for (int i = 0; i < entrants.length; i++) {
            if (entrants[i] != null) {
                entrantList.addItem(entrants[i]); // get entrants from entrant file and dd each to combo
            }
        }


        for (int a = 0; a < checkPoints.length; a++) {
            if (checkPoints[a] != 0) {
                checkPointList.addItem(checkPoints[a]);// add each checkpoint to combo
            }
        }


        // create a bottom JPanel to place everything on.
        JPanel totalGUI = new JPanel();

        // set the Layout Manager to null so we can manually place
        // the Panels.
        totalGUI.setLayout(null);

        // create a new panel, size it, shape it.
        // then add it to the bottom JPanel.
        JPanel topPanel = new JPanel((new GridLayout(3, 1)));
        topPanel.setLocation(0, 0);
        topPanel.setSize(300, 100);

        time.setText("Time");
        time.setSelected(true);
        time.addActionListener(this);

        medical.setText("Medical");
        medical.addActionListener(this);
        ButtonGroup group = new ButtonGroup();
        group.add(time);
        group.add(medical);

        JPanel radioPanel = new JPanel(new GridLayout(1, 1));
        radioPanel.add(time);
        radioPanel.add(medical);

        JLabel checkType = new JLabel("Checpoint Type:");
        JLabel nodeNum = new JLabel("Checpoint Number:");
        topPanel.add(checkType);
        topPanel.add(radioPanel);
        topPanel.add(nodeNum);
        topPanel.add(checkPointList);
        JLabel entrantName = new JLabel("Entrant:");
        topPanel.add(entrantName);
        topPanel.add(entrantList);
        totalGUI.add(topPanel);

        JPanel bottomPanel = new JPanel((new GridLayout(3, 1)));
        bottomPanel.setLocation(0, 100);
        bottomPanel.setSize(300, 150);
        submit = new JButton("Submit");
        submit.addActionListener(this);

        JPanel radioPanel2 = new JPanel(new GridLayout(1, 1));
        arrived.setText("Arrive-");
        departed.setText("Depart-");
        ButtonGroup group2 = new ButtonGroup();
        group2.add(arrived);
        group2.add(departed);
        departed.setEnabled(false);
        arrived.setSelected(true);
        radioPanel2.add(arrived);
        radioPanel2.add(departed);

        JLabel travel = new JLabel("Checpoint Type:");
        bottomPanel.add(travel);
        bottomPanel.add(radioPanel2);
        JSpinner.DateEditor de = new JSpinner.DateEditor(timeSpinner, "a:hh:mm");
        // create the JSpinner with a specific tim format e.g PM:01:20
        timeSpinner.setEditor(de);
        JLabel arrTime = new JLabel();
        arrTime.setText("<HTML>Set Arrival/ Departure Time <br>(Defualt as current):</HTML>");
        bottomPanel.add(arrTime);
        excluded.setText("Excluded?");
        excluded.setEnabled(false);
        bottomPanel.add(timeSpinner);
        bottomPanel.add(excluded);
        bottomPanel.add(submit);
        totalGUI.add(bottomPanel);

        // Finally we return the JPanel.
        totalGUI.setOpaque(true);
        return totalGUI;
    }

    @Override
    public void actionPerformed(ActionEvent evt) {

        String actionCommand = evt.getActionCommand();

        switch (actionCommand) {
            case "Submit":
                SimpleDateFormat format = new SimpleDateFormat("HH:mm");
                //convert the time on JSpinner to 24 hour time
                dateA = (Date) timeSpinner.getValue();
                String timeString = format.format(dateA);
                String checkType = "T";
                if (time.isSelected()) {
                    checkType = "T";
                } else { // else meaning medical is selected
                    if (excluded.isSelected()) {
                        checkType = "E";
                    } else {
                        if (departed.isSelected()) {
                            checkType = "D";
                        }
                        if (arrived.isSelected()) {
                            checkType = "A";
                        }
                    }
                }
                data dat = new data();
                Object selectedItem = checkPointList.getSelectedItem();
                String selectedItemStr = "";
                if (selectedItem != null) {
                    selectedItemStr = selectedItem.toString();
                }
                boolean check = dat.addUpdate(checkType, entrantArray[entrantList.getSelectedIndex()], Integer.parseInt(selectedItemStr), timeString, coursesArray, fileName);
                if (check == false) {
                    JOptionPane.showMessageDialog(null, "Note: Competitior Was Not Expected At That Location, CheckPoint File Updated", "Checkpoint Updated", JOptionPane.INFORMATION_MESSAGE);
                } else {
                    JOptionPane.showMessageDialog(null, "CheckPoint File Updated", "Checkpoint Updated", JOptionPane.INFORMATION_MESSAGE);

                }
                break;

            case "Time": // when the time radio button is enabled, disable medical checkpoint features
                departed.setEnabled(false);
                arrived.setSelected(true);
                excluded.setEnabled(false);
                excluded.setSelected(false);
                break;

            case "Medical": // enable extra features when medical radio button is selected
                departed.setEnabled(true);
                excluded.setEnabled(true);
                break;
        }
    }
}
