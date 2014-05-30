/* 
 * File:   main.c
 * Author: Craig
 *
 * Created on 11 December 2012, 12:50
 *
 * main file for the project, allowing users to select options from the menu
 * and linking these to the operations/ functions.
 * */

#include <stdio.h>
#include <stdlib.h>
#include "riders.h"

/*
 * 
 */


int main() {
    int what_next, nodes_n, tracks_n, courses_n, entrants_n;
    logFunction("---------------New Occasion Of Opening System-----------------");
    logFunction("Started Event Manager Program");
    //print title for the program
    printf("       __  ___   ____     _   __    ____  ______   ____     ____ \n");
    printf("      /  |/  /  / __ )   / | / /   /  _/ /_  __/  / __ (   / _  ( \n");
    printf("     / /|_/ /  / / / /  /  |/ /    / /    / /    / / / /  / /_/ / \n");
    printf("    / /  / /  / /_/ /  / /|  /   _/ /    / /    / /_/ /  / _, _/ \n");
    printf("   /_/  /_/   (____/  /_/ |_/   /___/   /_/     (____/  /_/ |_| \n");
    printf("                                                                        (Extended Version)\n\n");
    /*Set up arrays of structures for each of the groups of data, then pass these
     to the data functions which read in the information from the text files. 
     Populate the structs there.
     
     For the event structure, simply pass a pointer to the structure. */
    struct Event event_name;
    get_event(&event_name);

    struct Node nodes[30];
    nodes_n = get_nodes(nodes);

    struct Track tracks[30];
    tracks_n = get_tracks(tracks);

    struct Course courses[26];
    courses_n = get_courses(courses);

    struct Record entrants[30];
    entrants_n = get_entrants(entrants, courses, courses_n);

    //print the event information out
    printf("Welcome to system developed for:\n");
    printf("    %s\n", event_name.event);
    printf("    %s\n", event_name.date);
    printf("    %s\n\n", event_name.time);
    

    do {
        printf("       ******************************************************\n");
        printf("       *                                                    *\n");
        printf("       *             Please Select An Option:               *\n");
        printf("       *----------------------------------------------------*\n");
        printf("       * %2d.Locate Competitor                               *\n", LOCATE_COMPETITOR);
        printf("       * %2d.Count Competitors That Have Not Started         *\n", NOT_STARTED);
        printf("       * %2d.Count Competitors On Course                     *\n", ON_COURSE);
        printf("       * %2d.Count Competitors Finished                      *\n", HAVE_FINISHED);
        printf("       * %2d.Manually Supply Times                           *\n", MANUALLY_SUPPLY);
        printf("       * %2d.Supply Checkpoint Files                         *\n", CHECKPOINT);
        printf("       * %2d.Print Results                                   *\n", RESULTS_LIST);
        printf("       * %2d.Supply Medical Checkpoint Times                 *\n", MEDICAL_CHECKPOINT);
        printf("       * %2d.List Those Excluded For Wrong Routes            *\n", LIST_EXCLUDED_WRONG);
        printf("       * %2d.List Those Excluded For Medical Reasons         *\n", LIST_EXCLUDED_MEDICAL);
        printf("       *----------------------------------------------------*\n");
        printf("       * %2d.Quit                                            *\n", QUIT);
        printf("       ******************************************************\n");
        scanf("%d", &what_next);
        //print out the options, using the header file options

        /* based on the user's choice, do what they want */

        switch (what_next) {
            case LOCATE_COMPETITOR: /*Check user input to check if
                                                 the entrant number actually 
                                                 exists*/
                printf("\nPlease Input Competitor Number: ");
                int comp;
                scanf("%d", &comp);
                while (comp > entrants_n || comp < 1) {
                    printf("\nInvalid Competitor Number. Try Again: ");
                    logFunction("Entered Invalid Competitor Number When Looking Up");
                    scanf("%d", &comp);
                } /* pass in the structure argument to the function, along
                         the selected entrant number*/
                locate_competitor(entrants, comp);
                logFunction("Queried The Location A Competitor");
                printf("Type 'c' to continue..."); /* once complete, get the 
                                                       user to type 'c' to 
                                                       continue. then create
                                                       line space.*/
                while (getchar() != 'c') {
                }
                printf("\n\n\n\n\n\n\n\n");
                break;
            case NOT_STARTED:
                count_competitors_not_started(entrants, entrants_n);
                logFunction("Queried Competitors Not Started");
                printf("Type 'c' to continue...");
                while (getchar() != 'c') {
                }
                printf("\n\n\n\n\n\n\n\n");
                break;
            case ON_COURSE:
                count_competitors_started(entrants, entrants_n);
                logFunction("Queried Competitors On Course");
                printf("Type 'c' to continue...");
                while (getchar() != 'c') {
                }
                printf("\n\n\n\n\n\n\n\n");
                break;
            case HAVE_FINISHED:
                count_competitors_finished(entrants, entrants_n);
                logFunction("Queried Number Of Competitors Finished");
                printf("Type 'c' to continue...");
                while (getchar() != 'c') {
                }
                printf("\n\n\n\n\n\n\n\n");
                break;
            case MANUALLY_SUPPLY:
                printf("\nPlease Input Competitor Number: ");
                scanf("%d", &comp);
                while (comp > entrants_n || comp < 1) {
                    printf("\nInvalid Competitor Number. Try Again: ");
                    logFunction("Entered Invalid Competitor Number When Manually Supplying Checkpoint");
                    scanf("%d", &comp);
                }
                if (entrants[comp].excluded == 0) {
                    supply_manually(entrants, comp, nodes, tracks, tracks_n);
                } else {
                    printf("Sorry, Competitor Excluded.\n");
                }
                logFunction("Supplied Manually A Checkpoint Time");
                printf("Type 'c' to continue...");
                while (getchar() != 'c') {
                }
                printf("\n\n\n\n\n\n\n\n");
                break;
            case CHECKPOINT:
                supply_checkpoints(entrants, nodes, nodes_n, tracks, tracks_n);
                logFunction("Supplied Checkpoints File");
                printf("Type 'c' to continue...");
                while (getchar() != 'c') {
                }
                printf("\n\n\n\n\n\n\n\n");
                break;
            case RESULTS_LIST:
                print_results(entrants, entrants_n);
                logFunction("Printed A Results Table");
                printf("Type 'c' to continue...");
                while (getchar() != 'c') {
                }
                printf("\n\n\n\n\n\n\n\n");
                break;
            case MEDICAL_CHECKPOINT:
                printf("\nPlease Input Competitor Number: ");
                scanf("%d", &comp);
                while (comp > entrants_n || comp < 1) {
                    printf("\nInvalid Competitor Number. Try Again: ");
                    logFunction("Entered Invalid Competitor Number When Entering MCP");
                    scanf("%d", &comp);
                }
                if (entrants[comp].excluded == 0) {
                    supply_medical(entrants, comp);
                } else {
                    printf("Sorry, Competitor Excluded.\n");
                }
                logFunction("Inserted Medical Checkpoint Update For Entrant");
                printf("Type 'c' to continue...");
                while (getchar() != 'c') {
                }
                printf("\n\n\n\n\n\n\n\n");
                break;
            case LIST_EXCLUDED_WRONG:
                excluded_wrong_course(entrants, entrants_n);
                logFunction("Queried Competitors Excluded Competitors");
                printf("Type 'c' to continue...");
                while (getchar() != 'c') {
                }
                printf("\n\n\n\n\n\n\n\n");
                break;
            case LIST_EXCLUDED_MEDICAL:
                excluded_medical(entrants, entrants_n);
                logFunction("Queried Competitors Excluded At A Medical Checkpoint");
                printf("Type 'c' to continue...");
                while (getchar() != 'c') {
                }
                printf("\n\n\n\n\n\n\n\n");
                break;
            case QUIT:
                logFunction("Closed The System");
                break;
            default:
                printf("Incorrect Input\n\n");
                logFunction("Attempted An Invalid Option From The Main Menu");
                break;
        }
    } while (what_next != QUIT);



    return (EXIT_SUCCESS);
}

int logFunction(char *message){
    FILE * Output;
    Output = fopen("log.txt", "a");
    time_t mytime;
    mytime = time(NULL);
    
    fprintf(Output, message);
    fprintf(Output, " - ");
    fprintf(Output, ctime(&mytime));
    
    fclose(Output);
}
