/* 
 * File:   entrants.h
 * Author: Craig
 *
 * Created on 11 December 2012, 12:55
 */

#ifndef ENTRANTS_H
#define	ENTRANTS_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef ADD_H_GUARD
#define ADD_H_GUARD
    int locate_competitor(struct Record entrants[], int comp);
    int count_competitors_not_started(struct Record entrants[], int num_entrants);
    int count_competitors_started(struct Record entrants[], int num_entrants);
    int count_competitors_finished(struct Record entrants[], int num_entrants);
    int print_results(struct Record entrants[], int entrants_n);
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* ENTRANTS_H */

