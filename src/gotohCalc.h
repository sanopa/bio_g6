#ifndef _GOTOHCALC_H_
#define _GOTOHCALC_H_

#include <stdint.h>
#include "swCost.h"

struct cell {
	double scoreH;
  double scoreV;
  double scoreD;
	uint8_t prevsH;
  uint8_t prevsV;
  uint8_t prevsD;
};

struct matrix {
	unsigned int w;
	unsigned int h;
	struct cell *cells; /* pointer to array of w*h cells
			       cells[w*i+j] contains cell (i,j) */
};

/* allocate and initialize (first row and col) a matrix for SW
   alignment of strings s1 and s2 */
struct matrix *gotohInitMat(char *s1, char *s2);

/* Fill the mat matrix, using Smith-Waterman with a linear indel model
   using cost->indelOpen, or Gotoh with an affine indel model using
   cost->indelOpen and cost->indelExtend.
   Preconditions:
   - mat is correctly allocated and initialized (by swInitMat)
   - cost->subst is defined for each pair of letters in s1 and s2
*/
void gotohFillMat(struct matrix *mat, struct cost *cost, char *s1, char *s2) ;


/* free all allocated memory in mat */
void gotohFreeMat(struct matrix *mat);

/* print contents of matrix, for debugging */
void gotohPrintMat(struct matrix *mat);

#endif
