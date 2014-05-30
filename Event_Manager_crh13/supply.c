/* 
 * File:   entrants.c
 * Author: Craig
 *
 * Class holding supply functions for inputting checkpoint times selected from
 * the main menu. Uses the array of structures fro the entrants in all, along
 * with the nodes structure to decide what tracks the entrants are on.
 */

#include <stdio.h>
#include <stdlib.h>
#include "riders.h"
#include "supply.h"

/*
 * Allows user to input supply a checkpoint time and which checkpoint a certain
 * entrants has reached using input from keyboard. Takes in the array of
 * structures of entrants, along with the competitor number selected
 * and checked from the menu.
 */
int supply_manually(struct Record entrants[], int comp,struct Node nodes[], int nodes_s) {
    comp--; // deduct one to get the array number.
    int hours = 0;
    int mins = 0;
    char time[5];
    char time_copy[5];
    char * pch;
    int checkpoint = 0;
    int time_calc = 0;
    int check_node =0;
    
    if(entrants[comp].finished ==0){
    while(check_node == 0){
    printf("\nEnter a Time Checkpoint number the Competitor has Reached: ");
    logFunction("Entered Checkpoint Number Manually To Be Updated");
    scanf("%d", &checkpoint);
    checkpoint--;
    printf("%s", nodes[checkpoint].type);
    int i;
    for(i =0; i < nodes_s; i++){
        if (!strcmp(nodes[checkpoint].type, "CP")){
            check_node =1;
            break;
        }
    }
    if(check_node == 0){
        printf("\nInvalid Time Checkpoint Number!");
    }}
    strcpy(entrants[comp].cp_type, nodes[checkpoint].type);

    printf("\nEnter Current Time for Competitor (e.g  11:20): ");
    scanf("%s", time);
    logFunction("Entered Current Checkpoint Time Manually");

    strcpy(time_copy, time); // copy time into a temporary copy, to do work on it

    pch = strtok(time, ":"); // remove the ":" symbol from the time

    int count = 0;
    while (pch != NULL) {
        if (count == 0) {
            hours = atoi(pch);
        }// gets the hours from the first two numbers in the variable and 
            // places in a hours variable
        else {
            mins = atoi(pch);
            // gets the minutes
        }
        pch = strtok(NULL, " :");
        count++;
    }
    time_calc = (hours * 60) + mins; // to get total minutes, multiply out hours,
    // then add the remaining minutes
    if (entrants[comp].current_time < time_calc) { //can now compare
        entrants[comp].current_time = time_calc; //copy if newer
        strcpy(entrants[comp].time_s, time_copy);
        checkpoint++;
        entrants[comp].cp = checkpoint;
        entrants[comp].cp_count++;
    }
    if(entrants[comp].cp_count > 1){ 
        if (entrants[comp].cp == 1 ){
            entrants[comp].finished =1;}
    }
    }
    else {printf("Competitor Finished\n\n");}
}

/*
 *Takes in the entrants data, and node data here to supply checkpoints 
 * similar to previous function, but from a file that is read into the system.
 * Also takes in if the user has taken a wrong turn, or if they have arrived 
 * or departed at a medical checkpoint.
 */
int supply_checkpoints(struct Record entrants[], struct Node nodes[], int nodes_n, struct Track tracks, int track_n) {
    char fname[100];
    int check = 0;
    int array = 0;
    char status[2];
    int num = 0;
    int entrant = 0;
    int hours = 0;
    int mins = 0;
    char time[5];
    char * pch;
    int time_calc = 0;
    char time_copy[5];
    pch = time;

    
    FILE* fp;
    memset(fname, 0, 100);
    while (check == 0) {
        /*ask user for the name of the file*/
        printf("Enter file name for checkpoint file: ");
        logFunction("Entered Checkpoint File Name");
        scanf("%s", fname);

        //Opens the file from where the text will be read. 
        fp = fopen(fname, "r");

        //Checks if the file us unable to be opened, then it shows the error message 
        if (fp == NULL) {
            printf("\nError, No such file or directory.\n\n");
            logFunction("Entered Checkpoint File Name Incorrectly");
        } else {
            check = 1;
        }
    }
    while (!feof(fp)) {
        array += (fgetc(fp) == '\n'); //get number of checkpoints to be read
    }

    fclose(fp);
    fp = fopen(fname, "r");
    int i = 0;
    int x = 0;
    /* While not end of file */
    while (i < array) {
        fscanf(fp, "%s %d %d %[^\t\n]", status, &num, &entrant, time);
        printf("\n%s %d %d %s", status, num, entrant, time);
        entrant--;
        if(entrants[entrant].finished == 0){
        if (entrants[entrant].excluded == 0) {
            strcpy(time_copy, time); /*run the rest of the code for this entrant
                                   *provided they are not excluded */
            pch = strtok(time, ":"); // remove the ":" symbol from the time

            int count = 0;
            while (pch != NULL) {
                if (count == 0) {
                    hours = atoi(pch);
                }// gets the hours from the first two numbers in the variable and 
                    // places in a hours variable
                else {
                    mins = atoi(pch);
                    // gets the minutes
                }
                pch = strtok(NULL, " :");
                count++;
            }
            // to get total minutes, multiply out hours,
            // then add the remaining minutes

            x = 0;
            time_calc = (hours * 60) + mins;
            if (entrants[entrant].current_time < time_calc) {
                strcpy(entrants[entrant].time_s, time_copy);
                entrants[entrant].current_time = time_calc;
                entrants[entrant].cp = num; // set all relevant information
                while (x < nodes_n) {
                    if (nodes[x].node == num) { // loop through nodes to find what type
                        // of checkpoint it is
                        strcpy(entrants[entrant].cp_type, nodes[x].type);

                    }
                    x++;
                }
                
            }
            if (!strcmp(status, "I")) { /// find if the entrants should be excluded
                entrants[entrant].excluded = 1;
            }
            if (!strcmp(status, "E")) { /// find if the entrants should be excluded
                entrants[entrant].excluded = 2;
            }
             if (!strcmp(status, "A")) { /// 
                entrants[entrant].mcp = 1;
                 strcpy(entrants[entrant].cp_type, "MC");
                printf("%s", entrants[entrant].cp_type);
            }
            if (!strcmp(status, "D")) { /// 
                entrants[entrant].mcp = 2;
                 strcpy(entrants[entrant].cp_type, "MC");
            }
            entrants[entrant].cp_count++;
             if(entrants[entrant].cp_count > 1){ 
        if (entrants[entrant].cp == 1 ){
            entrants[entrant].finished =1;}
    }
        }} 
        i++;
    }
}


int supply_medical(struct Record entrants[], int comp) {
    comp--;
    int checkpoint;
    char status[1];
     int hours = 0;
    int mins = 0;
    char time[5];
    char time_copy[5];
    char * pch;
    int time_calc = 0;

    if(entrants[comp].finished == 0){
       
    printf("\nEnter the Medical Checkpoint number the Competitor has Reached/ Left: ");
    scanf("%d", &checkpoint);
    logFunction("Entered Medical Checkpoint Number");

    printf("\nLeft or Arrived? ('l'- left    'a'- arrived )");
    scanf("%s", status);
    logFunction("Entered Departed Or Arrived Status Of Checkpoint");
    
    

    if (!strcmp(status, "l")) {
        entrants[comp].mcp = 2;
        
        
    }
    else{
                entrants[comp].mcp = 1;

    }
    
    printf("\nEnter Current Time for Competitor (e.g  11:20): ");
    logFunction("Entered Medical Checkpoint Time");
    scanf("%s", time);
        

    
    strcpy(time_copy, time); // copy time into a temporary copy, to do work on it

    pch = strtok(time, ":"); // remove the ":" symbol from the time

    int count = 0;
    while (pch != NULL) {
        if (count == 0) {
            hours = atoi(pch);
        }// gets the hours from the first two numbers in the variable and 
            // places in a hours variable
        else {
            mins = atoi(pch);
            // gets the minutes
        }
        pch = strtok(NULL, " :");
        count++;
    }
    time_calc = (hours * 60) + mins; // to get total minutes, multiply out hours,
    // then add the remaining minutes
    if (entrants[comp].current_time < time_calc) { //can now compare
        entrants[comp].current_time = time_calc; //copy if newer
        strcpy(entrants[comp].time_s, time_copy);
        entrants[comp].cp = checkpoint;
        strcpy(entrants[comp].cp_type, "MC");
        entrants[comp].cp_count++;

    }}else{printf("Sorry, competitor finished");}
    
}
