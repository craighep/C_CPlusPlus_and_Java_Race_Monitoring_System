/* 
 * File:   data.h
 * Author: Craig
 *
 * Created on 11 December 2012, 12:55
 */

#ifndef DATA_H
#define	DATA_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef ADD_H_GUARD
#define ADD_H_GUARD
    int get_event(struct Event* e);
    int get_nodes(struct Node n_array[]);
    int get_tracks(struct Track track_array[]);
    int get_courses(struct Course course_array[]);
    int get_entrants(struct Record record_array[], struct Course courses[], int courses_n);
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* DATA_H */

