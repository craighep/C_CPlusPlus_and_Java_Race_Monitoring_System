/* 
 * File:   excluded.h
 * Author: Craig
 *
 * Created on 11 December 2012, 13:05
 */

#ifndef EXCLUDED_H
#define	EXCLUDED_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef ADD_H_GUARD
#define ADD_H_GUARD
    int excluded_wrong_course(struct Record entrants[], int entrants_n);
    int excluded_medical(struct Record entrants[], int entrants_n);
#endif





#ifdef	__cplusplus
}
#endif

#endif	/* EXCLUDED_H */

