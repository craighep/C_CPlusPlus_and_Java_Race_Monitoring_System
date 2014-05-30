/* 
 * File:   data.c
 * Author: Craig
 *
 * Class for providing functions that print lists of excluded entrants for 
 * either taking the wrong course or being excluded for medical reasons.
 */
#include <stdio.h>
#include <stdlib.h>
#include "riders.h"
#include "excluded.h"

/*
 *Method for printing the list of entrants excluded for taking the wrong route
 * on the course. 
 */
int excluded_wrong_course(struct Record entrants[], int entrants_n) {
    int i;
    printf("Excluded for wrong course:\n");
    /*Loops through the entrants array and checks if the status of the excluded
     variable is set to match the appropriate. If soo, print it.*/
    for (i = 0; i < entrants_n; i++) {
        if (entrants[i].excluded == 1) {
            printf("    %d %s", entrants[i].ID, entrants[i].name);
        }
    }
    printf("\n\n");
}

/*
 *Method for printing the list of entrants excluded for taking the wrong route
 * on the course. 
 */
int excluded_medical(struct Record entrants[], int entrants_n) {
    int i;
    printf("Excluded for safety reasons:\n");
    /*Loops through the entrants array and checks if the status of the excluded
     variable is set to match the appropriate. If soo, print it.*/
    for (i = 0; i < entrants_n; i++) {
        if (entrants[i].excluded == 2) {
            printf("    %d %s", entrants[i].ID, entrants[i].name);
        }
    }
    printf("\n\n");
}

