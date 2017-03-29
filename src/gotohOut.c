#include "gotohOut.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

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

void gotohPrintAlis(struct matrix *mat, struct cost *cost, char *s1, char *s2, char *chemin, char *chemin2, int i, int j, int prev) {
	struct cell c = mat->cells[mat->w*i+j];
	int s1loc = i;
	int s2loc = j;
	int prevs = prev;

	if (c.scoreD > 0) {
		if (prevs == 1) {
			if (cost->subst(s1[s1loc-1], s2[s2loc-1]) >= 0) {
				*chemin = s1[s1loc-1];
				*chemin2 = s2[s2loc-1];
			} else {
				*chemin = tolower(s1[s1loc-1]);
				*chemin2 = tolower(s2[s2loc-1]);
			}
			s1loc--;
			s2loc--;

			if (c.prevsD&1) {
				prevs = 1;
			} else if (c.prevsD&2) {
				prevs = 2;
			} else if (c.prevsD&4) {
				prevs = 4;
			}
			--chemin;
			--chemin2;
			gotohPrintAlis(mat, cost, s1, s2, chemin, chemin2, s1loc, s2loc, prevs);
		}
		if (prevs == 2) {
			*chemin = '-';
			*chemin2 = tolower(s2[s2loc-1]);
			s2loc--;
			if (c.prevsH&1) {
				prevs = 1;
			} else if (c.prevsH&2) {
				prevs = 2;
			} else if (c.prevsH&4) {
				prevs = 4;
			}
			--chemin;
			--chemin2;
			gotohPrintAlis(mat, cost, s1, s2, chemin, chemin2, s1loc, s2loc, prevs);
		}
		if (prevs == 4) {
			*chemin = tolower(s1[s1loc-1]);
			*chemin2 = '-';
			s1loc--;
			if (c.prevsV&1) {
				prevs = 1;
			} else if (c.prevsV&2) {
				prevs = 2;
			} else if (c.prevsV&4) {
				prevs = 4;
			}
			--chemin;
			--chemin2;
			gotohPrintAlis(mat, cost, s1, s2, chemin, chemin2, s1loc, s2loc, prevs);
		}
	} else {
		++chemin;
		++chemin2;

		printf("s1 alignment starts at %d, s2 starts at %d\n", s1loc+1, s2loc+1);
		printf("s1:\t%s\n", chemin);
		printf("s2:\t%s\n", chemin2);
	}
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

	int max = max2(strlen(s1), strlen(s2));
	for (unsigned int i = 1; i < h; i++){
		for (unsigned int j = 1; j < w; j++){
			if (mat->cells[w*i+j].scoreD == scoreMax) {
				char chemin_stockage[max+1];
				char chemin2_stockage[max+1];
				char *chemin = chemin_stockage + max;
				*chemin = '\0';

				char *chemin2 = chemin2_stockage + max;
				*chemin2 = '\0';

				--chemin;
				--chemin2;
				gotohPrintAlis(mat, cost, s1, s2, chemin, chemin2, i, j, 1);
			}
		}
	}

	// char chemin_stockage[max+1];
	// char chemin2_stockage[max+1];
	// struct cell c = mat->cells[w*imax+jmax];

	// char *chemin = chemin_stockage + max;
	// *chemin = '\0';

	// char *chemin2 = chemin2_stockage + max;
	// *chemin2 = '\0';

	// --chemin;
	// --chemin2;

	// int s1loc = imax;
	// int s2loc = jmax;
	// int prevs = 1;
	// int occBreak =0;
	// while (c.scoreD > 0 ) {
	// 	if (prevs == 1) {
	// 		if (cost->subst(s1[s1loc-1], s2[s2loc-1]) >= 0) {
	// 			*chemin = s1[s1loc-1];
	// 			*chemin2 = s2[s2loc-1];
	// 		} else {
	// 			*chemin = tolower(s1[s1loc-1]);
	// 			*chemin2 = tolower(s2[s2loc-1]);
	// 		}
	// 		s1loc--;
	// 		s2loc--;

	// 		if (c.prevsD&1) {
	// 			prevs = 1;
	// 		} else if (c.prevsD&2) {
	// 			prevs = 2;
	// 		} else if (c.prevsD&4) {
	// 			prevs = 4;
	// 		}else{
	// 			printf("i=%i, j=%i \n", s1loc,s2loc);
	// 			printf("coucou prevs 1\n");
	// 			occBreak=1;
	// 			break;
	// 		}
	// 		--chemin;
	// 		--chemin2;
	// 		c = mat->cells[w*s1loc+s2loc];
	// 	} else if (prevs == 2) {
	// 		*chemin = '-';
	// 		*chemin2 = tolower(s2[s2loc-1]);
	// 		s2loc--;
	// 		if (c.prevsH&1) {
	// 			prevs = 1;
	// 		} else if (c.prevsH&2) {
	// 			prevs = 2;
	// 		} else if (c.prevsH&4) {
	// 			prevs = 4;
	// 		}
	// 		else{
	// 			printf("i=%i, j=%i \n", s1loc,s2loc);
	// 			printf("le score vaut %f \n", mat->cells[w*s1loc+s2loc].scoreD);
	// 			printf("les prevs valent D=%i, H=%i, V=%i \n", c.prevsD, c.prevsH, c.prevsV);
	// 			printf("coucou depuis prevs==2 \n");
	// 			occBreak=1;
	// 			break;
	// 		}
	// 		--chemin;
	// 		--chemin2;
	// 		c = mat->cells[w*s1loc+s2loc];
	// 	} else if (prevs == 4) {
	// 		*chemin = tolower(s1[s1loc-1]);
	// 		*chemin2 = '-';
	// 		s1loc--;
	// 		if (c.prevsV&1) {
	// 			prevs = 1;
	// 		} else if (c.prevsV&2) {
	// 			prevs = 2;
	// 		} else if (c.prevsV&4) {
	// 			prevs = 4;
	// 		}
	// 		else{
	// 			printf("i=%i, j=%i \n", s1loc,s2loc);
	// 			printf("le score vaut %f \n", mat->cells[w*s1loc+s2loc].scoreD);
	// 			printf("les prevs valent D=%i, H=%i, V=%i \n", c.prevsD, c.prevsH, c.prevsV);
	// 			printf("coucou prevs 4\n");
	// 			occBreak=1;
	// 			break;

	// 		}
	// 		--chemin;
	// 		--chemin2;
	// 		c = mat->cells[w*s1loc+s2loc];
	// 	} else{
	// 		printf("coucou pas dans un prev ! \n");

	// 	}
	// }

	// /*fin ajout débug */
	// ++chemin;
	// ++chemin2;
	// if (occBreak){
	// 	printf("il y a eu u n break \n");
	// }
	// printf("s1 alignment starts at %d, s2 starts at %d\n", s1loc+1, s2loc+1);
	// printf("s1:\t%s\n", chemin);
	// printf("s2:\t%s\n", chemin2);
}
