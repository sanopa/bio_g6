#include <stdio.h>
#include <stdlib.h>

#include "swCost.h"
#include "gotohCalc.h"
#include "swGetSeq.h"
#include "gotohOut.h"

int main(void)
{
	char *s1 ;
	while((s1 = getSeq(1)) == NULL) {
		// nothing to do
	}
	char *s2 ;
	while((s2 = getSeq(1)) == NULL) {
	}
	printf("Sequences read:\ns1\t%s\ns2\t%s\n\n", s1, s2) ;

	/* BLOSUM62 prot subst cost with affine cost for short indels */
	struct cost *cost = costProt(-10,-0.5);
	struct matrix *mat = gotohInitMat(s1,s2);
	gotohFillMat(mat,cost,s1,s2);
	/* for debugging you can uncomment:
	   swPrintMat(mat); */
	gotohprintBestAlis(mat,cost,s1,s2);

	gotohFreeMat(mat);
	free(cost);
	free(s1);
	free(s2);
	return(0);
}
