/* 
 * File:   supply.h
 * Author: Craig
 *
 * Created on 11 December 2012, 12:55
 */

#ifndef SUPPLY_H
#define	SUPPLY_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef ADD_H_GUARD
#define ADD_H_GUARD
    int supply_manually(struct Record entrants[], int comp, struct Node nodes[], int nodes_s);
    int supply_checkpoints(struct Record entrants[], struct Node nodes[], int nodes_n, struct Track tracks, int track_n);
    int supply_medical(struct Record entrants[], int comp);
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SUPPLY_H */

