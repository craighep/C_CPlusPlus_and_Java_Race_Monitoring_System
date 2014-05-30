/* 
 * File:   data.c
 * Author: Craig
 *
 * Class holding all the methods for reading in initial data from the text
 * files. Each function takes in the structures from the main menu to populate 
 * them.
 */

#include <stdio.h>
#include <stdlib.h>
#include "riders.h"
#include "data.h"

/*
 * Gets the event information from the 'name.txt' file, getting such data as
 * the event name, date and time of the event.  Uses fscanf to get and place 
 * these in the structure.
 */
int get_event(struct Event* e) {
    char fname[100];
    char event [50];
    char date [30];
    char time [5];
    int check = 0;

    FILE* fp;
    memset(fname, 0, 100);
    while (check == 0) {
        /*ask user for the name of the file*/
        printf("Enter file name for event name: ");
        scanf("%s", fname);

        //Opens the file from where the text will be read. 
        fp = fopen(fname, "r");

        //Checks if the file us unable to be opened, then it shows the error message 
        if (fp == NULL) {
            printf("\nError, No such file or directory.\n\n");
        } else {
            check = 1;
        }
    }
    fclose(fp);
    fp = fopen(fname, "r");
    // fscanf all the variables from the file.
    fscanf(fp, "%[^\t\n] %[^\t\n] %[^\t\n]", event, date, time);
    strcpy(e->event, event);
    strcpy(e->date, date);
    strcpy(e->time, time);
    //copy the data to the pointers in the event structure
    printf("%s\n", e->event);
    printf("%s\n", e->date);

    printf("%s\n", e->time);

    /* End while */
    fclose(fp); /* fclose closes the file */



}

/*
 * Gets the nodes information from the 'nodes.txt' file, getting such data as
 * the node numbers and checkpoint types.  Uses fscanf to get and place 
 * these in the structure.
 */
int get_nodes(struct Node n_array[]) {


    char fname[100];
    int node = 1;
    char type [2];
    int check = 0;
    int array;

    FILE* fp;
    memset(fname, 0, 100);
    while (check == 0) {
        /*ask user for the name of the file*/
        printf("Enter file name for nodes: ");
        scanf("%s", fname);

        //Opens the file from where the text will be read. 
        fp = fopen(fname, "r");

        //Checks if the file us unable to be opened, then it shows the error message 
        if (fp == NULL) {
            printf("\nError, No such file or directory.\n\n");
        } else {
            check = 1;
        }
    }
    char line[1024];
    array = 1; //gets number of entrants
    while (fgets(line, sizeof (line), fp) != NULL) {
        array++;
    }


    fclose(fp);
    fp = fopen(fname, "r");
    int i = 0;
    int node_x = 1;
    /* While not end of file */
    while (!feof(fp)) {
        fscanf(fp, "%d %s", &node, type);
        n_array[i].node = node_x;
        strcpy(n_array[i].type, type);
        printf("%d %s\n", n_array[i].node, n_array[i].type);
        i++;
        node_x++;
    }
    /* End while */
    fclose(fp); /* fclose closes the file */
    return array;
}

/*
 * Gets the track information from the 'tracks.txt' file, getting such data as
 * the track ID, track start and finish nodes, along with the
 * allowed time for the track.  Uses fscanf to get and place 
 * these in the structure.
 */
int get_tracks(struct Track track_array[]) {
    char fname[100];
    int track_ID = 0;
    int array;
    int node1 = 0;
    int node2 = 0;
    int allo_time = 0;
    int check = 0;

    FILE* fp;
    memset(fname, 0, 100);
    while (check == 0) {
        /*ask user for the name of the file*/
        printf("Enter file name for tracks: ");
        scanf("%s", fname);
        //Opens the file from where the text will be read. 
        fp = fopen(fname, "r");

        //Checks if the file us unable to be opened, then it shows the error message 
        if (fp == NULL) {
            printf("\nError, No such file or directory.\n\n");
        } else {
            check = 1;
        }
    }
    char line[1024];
    array = 0; //gets number of entrants
    while (fgets(line, sizeof (line), fp) != NULL) {
        array++;
    }




    fclose(fp);
    fp = fopen(fname, "r");
    int i = 0;
    /* While not end of file */
    while (!feof(fp)) {
        fscanf(fp, "%d %d %d %d", &track_ID, &node1, &node2, &allo_time);
        track_array[i].track_ID = track_ID;
        track_array[i].node1 = node1;
        track_array[i].node2 = node2;
        track_array[i].allo_time = allo_time;

        i++;
    }
    int x = 0;
    while (x <= array) {
        printf("%d %d %d %d\n", track_array[x].track_ID, track_array[x].node1, track_array[x].node2, track_array[x].allo_time);
        x++;
    }

    /* End while */
    fclose(fp); /* fclose closes the file */
    return array;

}

/*
 * Gets the course information from the 'course.txt' file, getting such data as
 * the course ID, course nodes and size of course.  Uses fscanf to get and place 
 * these in the structure.
 */
int get_courses(struct Course course_array[]) {

    char fname[100];
    char course_ID [1];
    int size = 0;
    int array = 0;
    int node = 0;
    int check = 0;


    FILE* fp;
    memset(fname, 0, 100);
    while (check == 0) {
        /*ask user for the name of the file*/
        printf("Enter file name for courses: ");
        scanf("%s", fname);
        //Opens the file from where the text will be read. 
        fp = fopen(fname, "r");

        //Checks if the file us unable to be opened, then it shows the error message 
        if (fp == NULL) {
            printf("\nError, No such file or directory.\n\n");
        } else {
            check = 1;
        }
    }
    while (!feof(fp)) { // while not at end of file
        array += (fgetc(fp) == '\n');
    }

    fclose(fp);
    fp = fopen(fname, "r");
    int i = 0;
    int x = 0;
    /* While not end of file */
    while (i < array) {
        fscanf(fp, "%s %d", course_ID, &size);
        strcpy(course_array[i].course_ID, course_ID);
        course_array[i].size = size;
        printf("%s %d ", course_array[i].course_ID, course_array[i].size);
        while (x != size) { // scan each node of the course
            fscanf(fp, "\n%d", &node);
            course_array[i].nodes_array[x] = node;
            printf("%d ", course_array[i].nodes_array[x]);
            x++;
        }
        printf("\n");

        x = 0;
        i++;
    }

    /* End while */
    fclose(fp); /* fclose closes the file */
    return array; //returns the number of courses.
}

/*
 * Gets the entrants information from the 'entrants.txt' file, getting such data as
 * the ID, course allocated and  full name.  Uses fscanf to get and place 
 * these in the structure.
 */
int get_entrants(struct Record record_array[], struct Course courses[], int courses_n) {

    char fname[100];
    char name[50];
    int ID = 0;
    int array = 0;
    char course[1];
    int check = 0;

    FILE* fp;
    memset(fname, 0, 100);
    while (check == 0) {
        /*ask user for the name of the file*/
        printf("Enter file name for entrants: ");
        scanf("%s", fname);
        //Opens the file from where the text will be read. 
        fp = fopen(fname, "r");

        //Checks if the file us unable to be opened, then it shows the error message 
        if (fp == NULL) {
            printf("\nError, No such file or directory.\n\n");
        } else {
            check = 1;
        }
    }
    while (!feof(fp)) { // while not at end of file
        array += (fgetc(fp) == '\n');
    }

    fclose(fp);
    fp = fopen(fname, "r");
    int i = 0;
    int t = array;
    /* While not end of file */
    while (i < t) {
        fscanf(fp, "%d %s %[^\t\n]", &ID, course, name);

        strcpy(record_array[i].course, course);
        int z;
        for (z = 0; z < courses_n; z++) {
            if (!strcmp(courses[z].course_ID, record_array[i].course)) {
                record_array[i].course_num = z;
            }
        }
        record_array[i].ID = ID;
        strcpy(record_array[i].name, name);
        record_array[i].current_time = 0;
        record_array[i].finished = 0;
        record_array[i].cp_count = 0;
        record_array[i].excluded = 0;
        record_array[i].cp = 0;
        record_array[i].cp_count = 0;
        record_array[i].track = 0; // initialise all the structure variables

        printf("%d %s %s\n", record_array[i].ID, record_array[i].course, record_array[i].name);
        i++;
    }
    printf("\n");


    /* End while */
    fclose(fp); /* fclose closes the file */
    return t;
}








