/* 
 * File:   entrants.c
 * Author: Craig
 *
 * Functions present within this source file are responsible for dealing
 * with entrant information such as printing location, printing the number not 
 * started and printing the results table.
 * Uses the array of structures from the main class to get information
 */

#include <stdio.h>
#include <stdlib.h>
#include "riders.h"
#include "entrants.h"

/*
 * Function for locating a competitor and printing out what time they are on, if
 * they are started/ finished, or if they are excluded. Also prints the track 
 * and course number entrant is on/ registered for.
 */
int locate_competitor(struct Record entrants[], int comp) {

    comp--; /* deduct one from competitor variable to match the correct array 
             number up because arrays start at 0.. */

    if (entrants[comp].excluded > 0) { // check if entrants are excluded
        if (entrants[comp].excluded == 1) { // look which type of exclusion
            printf("\nCompetitor %d, %s has been excluded from Course %s, for taking incorrect route\n\n", entrants[comp].ID, entrants[comp].name, entrants[comp].course);
        } else {
            printf("\nCompetitor %d, %s has been excluded from Course %s, for medical safety reasons\n\n", entrants[comp].ID, entrants[comp].name, entrants[comp].course);
        }

    } else if (entrants[comp].finished == 1) { // check if entrants finished
        printf("\nCompetitor %d, %s has finished Course %s, Time %s\n\n", entrants[comp].ID, entrants[comp].name, entrants[comp].course, entrants[comp].time_s);
    }

    else if (entrants[comp].current_time == 0) { // if time is 0, must be entrants have not started
        printf("\nCompetitor %d, %s has not started yet- Course %s\n\n", entrants[comp].ID, entrants[comp].name, entrants[comp].course, entrants[comp].time_s);
    }
    else if (!strcmp(entrants[comp].cp_type, "MC")) { // look too see which checkpoint type it is
        if (entrants[comp].mcp == 1) {
            printf("\nCompetitor %d, %s has arrived at a medical checkpoint on Course %s, Current time %s\n\n", entrants[comp].ID, entrants[comp].name, entrants[comp].course, entrants[comp].time_s);
        } else {
            printf("\nCompetitor %d, %s has departed at a medical checkpoint on Course %s, Current time %s\n\n", entrants[comp].ID, entrants[comp].name, entrants[comp].course, entrants[comp].time_s);
        }
    }

    else if (entrants[comp].cp_type == "CP") {
        printf("\nCompetitor %d, %s is at a time checkpoint on Course %s, Current time %s\n\n", entrants[comp].ID, entrants[comp].name, entrants[comp].course, entrants[comp].time_s);
    }
    else { // if all are untrue, entrants must be on track currently
        printf("\n%s Competitor %d, %s is on Track %d, Course %s, Current time %s\n\n", entrants[comp].cp_type, entrants[comp].ID, entrants[comp].name, entrants[comp].track, entrants[comp].course, entrants[comp].time_s);

    }
}

/*Function for counting the number of entrants yet to start. Loops through the
 array of entrant structures, and adds one to a count if their status for 
 current time is 0*/
int count_competitors_not_started(struct Record entrants[], int num_entrants) {
    int not_started = 0;
    int i;
    for (i = 0; i < num_entrants; i++) {
        if (entrants[i].current_time == 0) {
            not_started++;
        }
    }
    printf("\nNumber of Competitors not Started: %d\n\n", not_started);

}

/*Function for counting the number of entrants started. Loops through the
 array of entrant structures, and adds one to a count if their status for 
 current time is not 0, and they are not excluded.*/
int count_competitors_started(struct Record entrants[], int num_entrants) {
    int started = 0;
    int i;
    for (i = 0; i < num_entrants; i++) {
        if (entrants[i].current_time != 0) {
            if (entrants[i].excluded == 0) {
                if (entrants[i].finished != 1) {
                    started++;
                }

            }
        }
    }
    printf("\nNumber of Competitors on Course: %d\n\n", started);
}

/*Function for counting the number of entrants finished. Loops through the
 array of entrant structures, and adds one to a count if their status for 
 finished is 1. (true)*/
int count_competitors_finished(struct Record entrants[], int num_entrants) {
    int finished = 0;
    int i;
    for (i = 0; i < num_entrants; i++) {
        if (entrants[i].finished == 1) {
            finished++;
        }
    }
    printf("\nNumber of Competitors Finished: %d\n\n", finished);

}

/*Takes in the array of structures for entrants, then loops through these
 printing out important information such as their course, last recorded time
 and the track they are on..*/

/*Takes in the array of structures for entrants, then loops through these
 printing out important information such as their course, last recorded time
 and the track they are on..*/
int print_results(struct Record entrants[], int entrants_n) {
    char started[3];
    char finished[3] = "no ";
    char blank[1]; // used to align the table records
    char time[5];
    int node;
    int i;

    printf("\n|   Comp-Num:   |    Started?    |    Course:    |     Last Rec Time:     |       Last Seen:     |     Track?:     |     Finished? |\n");
    printf("  -----------------------------------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < entrants_n; i++) {
        if (entrants[i].current_time == 0) {
            strcpy(started, "no ");
            strcpy(time, "     "); // if no time is present, fill the gap with spaces
        } else {
            strcpy(started, "yes");
            strcpy(time, entrants[i].time_s);
        }

        if (entrants[i].cp == 1) {
            if (entrants[i].cp_count > 1) {
                strcpy(finished, "yes");
            }
        }

        if (i < 9) {
            strcpy(blank, " "); // add a space to number if less than 10
        } else {
            strcpy(blank, "");
        }






        printf("         %d %s             %s              %s                   %s                     %d,%s               %d              %s     \n", entrants[i].ID, blank, started, entrants[i].course, time, entrants[i].cp, entrants[i].cp_type, entrants[i].track, finished);
    }

}


