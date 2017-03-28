#ifndef _GOTOHOUT_H_
#define _GOTOHOUT_H_

#include "gotohCalc.h"
#include "swCost.h"

/* Find highest scoring local alignment(s) in mat, and print to stdout
   the corresponding best alignments.
   mat must have been filled with scores and prevs.
   cost is provided so mismatches with negative scores can be lowercased.
*/
void gotohprintBestAlis(struct matrix *mat, struct cost *cost, char *s1, char *s2) ;

#endif
