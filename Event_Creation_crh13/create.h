/* 
 * File:   create.h
 * Author: Craig
 *
 * Created on 27 February 2013, 14:41
 */

#define	CREATE_H




#ifdef	__cplusplus
extern "C" {
#endif
#define SET_EVENT 1
#define SET_ENTRANTS 2
#define SET_COURSES 3
#define QUIT 4

#ifndef ADD_H_GUARD
#define ADD_H_GUARD
    int get_event();
    int get_entrants();
    int get_courses();
    int clearInput();


#ifdef	__cplusplus
}
#endif

#endif	/* CREATE_H */

