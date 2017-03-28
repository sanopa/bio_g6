#include "gotohOut.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>


static double max2(int a1, int a2) {
	if (a1 < a2) {
		return a2;
	} else {
		return a1;
	}
}

static double max3(int a1, int a2, int a3) {
  double res = a1;
	if (res < a2) {
		res = a2;
	}
  if (res < a3){
		res = a3;
	}
  return res;
}


void gotohprintBestAlis(struct matrix *mat, struct cost *cost, char *s1, char *s2){
	unsigned int h = mat->h;
	unsigned int w = mat->w;
	double scoreMax = 0;
	int imax = 0;
	int jmax = 0;
	for (unsigned int i =1; i < h; i++){
		for (unsigned int j = 1; j < w; j++){
			if (mat->cells[w*i+j].scoreD > scoreMax){
				scoreMax = mat->cells[w*i+j].scoreD ;
				imax = i;
				jmax = j;
			}
		}
	}
  //Les alignements optimaux commencent et terminent forcément par un match (ou un mismatch de
  //score positif), on les trouvera donc dans la matrice D.
	printf("Best score is %.2f, the best scoring alignments are: \n", scoreMax);

	// int max = max2(strlen(s1), strlen(s2));
	// char chemin_stockage[max+1];
	// char chemin2_stockage[max+1];
	// struct cell c = mat->cells[w*imax+jmax];
  //
	// char *chemin = chemin_stockage + max;
	// *chemin = '\0';
  //
	// char *chemin2 = chemin2_stockage + max;
	// *chemin2 = '\0';
  //
	// --chemin;
	// --chemin2;
  //
	// int s1loc = imax;
	// int s2loc = jmax;
  //
	// while (c.score > 0) {
	// 	if (c.prevs&1){
	// 		if (cost->subst(s1[s1loc-1], s2[s2loc-1]) > 0) {
	// 			*chemin = s1[s1loc-1];
	// 			*chemin2 = s2[s2loc-1];
	// 		} else {
	// 			*chemin = tolower(s1[s1loc-1]);
	// 			*chemin2 = tolower(s2[s2loc-1]);
	// 			printf("on est ici et on a s1=%c, s2=%c \n", *chemin, *chemin2);
	// 		}
	// 		s1loc--;
	// 		s2loc--;
	// 	} else if (c.prevs&2){
	// 		*chemin = '-';
	// 		*chemin2 = s2[s2loc-1];
	// 		s2loc--;
	// 	}  else if (c.prevs&4) {
	// 		*chemin = s1[s1loc-1];
	// 		*chemin2 = '-';
	// 		s1loc--;
	// 	}
	// 	--chemin;
	// 	--chemin2;
	// 	c = mat->cells[w*s1loc+s2loc];
	// }
  //
	// ++chemin;
	// ++chemin2;
  //
	// printf("s1 alignment starts at %d, s2 starts at %d\n", s1loc+1, s2loc+1);
	// printf("s1:\t%s\n", chemin);
	// printf("s2:\t%s\n", chemin2);
}
