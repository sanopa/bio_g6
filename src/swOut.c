#include "swOut.h"
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

// void printAli(char *chemin, char *chemin2, struct matrix *mat, int i, int j, char *s1, char *s2) {
// 	uint8_t prev = mat->cells[w*i+j].prevs;

// 	if (c.prevs&1){
// 		double score = 
// 		*chemin = mat->cells[w*(i-1)+(j)].score
// 		printAli
// 	}
// 	if (c.prevs&2){
// 		printf("l");
// 	}
// 	if(c.prevs&4){
// 		printf("t");
// 	}		
// }

void printBestAlis(struct matrix *mat, struct cost *cost, char *s1, char *s2){
	unsigned int h = mat->h;
	unsigned int w = mat->w;
	double scoreMax = 0;
	int imax = 0;
	int jmax = 0;
	for (unsigned int i =1; i < h; i++){
		for (unsigned int j = 1; j < w; j++){
			if (mat->cells[w*i+j].score > scoreMax){
				scoreMax = mat->cells[w*i+j].score ; 
				imax = i;
				jmax = j;
			}
		}
	}
		
	printf("Best score is %.2f, the best scoring alignments are: \n", scoreMax);

	int max = max2(strlen(s1), strlen(s2));
	char chemin_stockage[max+1];
	char chemin2_stockage[max+1];
	struct cell c = mat->cells[w*imax+jmax];

	char *chemin = chemin_stockage + max;
	*chemin = '\0';

	char *chemin2 = chemin2_stockage + max;
	*chemin2 = '\0';

	--chemin;
	--chemin2;

	int s1loc = imax;
	int s2loc = jmax;
	
	while (c.score > 0) {
		if (c.prevs&1){
			if (cost->subst(s1[s1loc], s2[s2loc]) > 0) {
				*chemin = s1[s1loc];
				*chemin2 = s2[s2loc];
			} else {
				*chemin = tolower(s1[s1loc]);
				*chemin2 = tolower(s2[s2loc]);
			}
			s1loc--;
			s2loc--;
		} else if (c.prevs&2){
			*chemin = '-';
			*chemin2 = s2[s2loc];
			s2loc--;
		}  else if (c.prevs&4) {
			*chemin = s1[s1loc];
			*chemin2 = '-';
			s1loc--;
		}
		--chemin;
		--chemin2;
		c = mat->cells[w*s1loc+s2loc];
	}

	*chemin = s1[s1loc];
	*chemin2 = s2[s2loc];

	printf("s1 alignment starts at %d, s2 starts at %d\n", s1loc+1, s2loc+1);
	printf("s1:\t%s\n", chemin);
	printf("s2:\t%s\n", chemin2);
}