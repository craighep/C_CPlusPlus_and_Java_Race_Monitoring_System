/* 
 * File:   main.cpp
 * Author: Craig
 *
 * Program intended for creating basic data files for an event. This includes
 * methods for creating an event (name, date and time), creating a set of 
 * entrants for that event, and creating a list of nodes on the courses.
 * Created on 27 February 2013, 08:27
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include "create.h"
using namespace std;

/*
 * Create a structure for each event, entrant and courses in order to
 * encapsulate infromation
 */
struct event {
    string name;
    string date;
    string time;
};

struct entrant {
    string name;
    int ID;
    string course;
};

struct course {
    string course;
    int node[20];
    int nodes;
};

/*
 * Main method containing main menu of the program offering options to the user.
 * user can select an operation e.g. creating an event, then when complete 
 * return to the menu for next selection.
 */
int main(int argc, char** argv) {
    int what_next; /* holds the users selection*/
    do {
        printf("       ******************************************************\n");
        printf("       *                                                    *\n");
        printf("       *             Please Select An Option:               *\n");
        printf("       *----------------------------------------------------*\n");
        printf("       * %2d.Enter An Event                                  *\n", SET_EVENT);
        printf("       * %2d.Enter The Entrants For Event                    *\n", SET_ENTRANTS);
        printf("       * %2d.Enter Courses Nodes For Event                   *\n", SET_COURSES);
        printf("       *----------------------------------------------------*\n");
        printf("       * %2d.Quit                                            *\n", QUIT);
        printf("       ******************************************************\n");
        cin >> what_next;
        /*print out the options, using the header file options*/

        /* based on the user's choice, do what they want */

        switch (what_next) {
            case SET_EVENT:
                get_event();
                cout << "\n\n\n\n\n\n\n\n"; /* clear screen after function */
                break;
            case SET_ENTRANTS:
                get_entrants();
                cout << "\n\n\n\n\n\n\n\n";
                break;
            case SET_COURSES:
                clearInput();
                get_courses();
                cout << "\n\n\n\n\n\n\n\n";
                break;
            case QUIT:
                break;
            default:
                cout << "Incorrect Input\n\n";
                break;
        }
    } while (what_next != QUIT);

    return 0;
}

/*
 *Method for getting the event to be created by inputs from users. Uses 
 * cin getline function to get the whole line inputted as a string, then simply 
 * adds this to the event structure where it is then outputted to file.
 */
int get_event() {

    event event; // create a new event structure
    clearInput(); // clear input when input previously uses cin
    cout << "Please Input Event Name: ";
    getline(cin, event.name); // get event name and store within the event structure
    cout << "Please Input Event Date(e.g 25th June 2012): ";
    getline(cin, event.date);
    cout << "Please Input Event Time(e.g 09:10): ";
    getline(cin, event.time);

    ofstream myfile;
    myfile.open("name.txt"); // open a file named "name.txt" or create it if it does not exist
    myfile << event.name + "\n"; // output event name followed by new line character
    myfile << event.date + "\n";
    myfile << event.time;
    myfile.close(); // close file once everything is written

}

/*
 *Methods used to get entrants for an event. Does this by creating an array of
 * entrants of type entrant depending on how many entrants the user says there is.
 * Then runs through this array printing each to the entrants file.
 */
int get_entrants() {
    int entrants = 1;
    int id = 1;

    cout << "How Many Entrants Are There?: ";
    cin >> entrants; // get number of entrants in event
    clearInput();

    if (entrants > 0) {
        entrant entrant_array[entrants]; // create array of entrants type entrant

        for (int i = 0; i < entrants; i++) { // for each entrant in the array
            cout << "Please Enter Entrants Full Name: ";
            getline(cin, entrant_array[i].name); //get the entrants name and add to structure
            cout << "Please Enter Entrants Course: ";
            getline(cin, entrant_array[i].course);
        }
        ofstream myfile;
        myfile.open("entrants.txt"); // open the entrants text file
        for (int a = 0; a < entrants; a++) { // for each entrant, write entrant details
            myfile << id;
            myfile << " " + entrant_array[a].course + " ";
            myfile << entrant_array[a].name + "\n";
            id++;
        }
        myfile.close();
    }
}

/*
 *Method for allowing user input of courses, outlining their nodes for each one.
 * Checks if nodes exists, ensuring a course does not have an invalid course 
 * node.
 */
int get_courses() {
    int courses;

    string fileName;
    cout << "Input Filename For Nodes: ";
    getline(cin, fileName); // get the node filename

    ifstream inData;
    inData.open(fileName.c_str()); // check if the nodes file is not empty
    if (!inData)
        return 0;

    int size = 0;
    string line;
    while (!inData.eof()) // get the size of the nodes file, depicting the amount of nodes.
    {
        getline(inData, line);
        size++;
    }
    size--; // remove one from size, as program will have read an extra line


    cout << "How Many Courses Do You Want To Input?: ";
    cin >> courses; // get amount of courses to be written
    course course_array[courses]; // create an array of courses, of type course

    for (int i = 0; i < courses; i++) { //for each course
        cout << "Enter Course Letter: ";
        cin >> course_array[i].course; //get the course letter
        clearInput();
        cout << "How Many Nodes Are On This Course?: "; //find out how many nodes are to be input
        cin >> course_array[i].nodes;
        clearInput();

        int identify = 1;
        bool check = true;
        for (int a = 0; a < course_array[i].nodes; a++) {
            do {
                check = false;
                cout << "Input Node: " << identify << ":"; // ask for specific node on course

                cin >> course_array[i].node[a]; // get node from user input
                if (course_array[i].node[a] > size) { // check if node exists
                    cout << "Node Does Not Exist. Try Again.";
                    check = true;
                }
            } while (check == true);
            identify++;
        }
    }

    ofstream myfile;
    myfile.open("courses.txt"); // open courses file to be written to
    for (int a = 0; a < courses; a++) {
        myfile << course_array[a].course; // write course letter to each line
        myfile << " " << course_array[a].nodes;
        for (int b = 0; b < course_array[a].nodes; b++) {
            myfile << " " << course_array[a].node[b]; // write out each course node
        }
        myfile << "\n"; // end each line with new line character
    }
    myfile.close(); // close file after writing
}

/*
 *This short method simply clears the input buffer and is used before a 
 * readline input after a cin input. It removes the newline character gained
 * from a previous cin.
 */
int clearInput() {

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}
