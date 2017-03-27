#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "mem.h"
#include "swCalc.h"
#include "swCost.h"

static double max(double a1, double a2, double a3, double a4){
	double res = a1;
	if (a1 < a2){
		res = a2;
	}
	if (res < a3){
		res = a3;
	}
	if (res < a4){
		res = a4;
	}
	return res;
}

struct matrix *swInitMat(char *s1, char *s2) {
	int len_s1 = strlen(s1);
	int len_s2 = strlen(s2);


	struct matrix *m = mallocOrDie(sizeof(struct matrix), "malloc died a second time");
	m->w = len_s2 + 1;
	m->h = len_s1 + 1;

	struct cell *cells = mallocOrDie(sizeof(struct cell)*(len_s1 + 1) * (len_s2 + 1), "malloc died");
	for (unsigned int i = 0; i < m->h; i++) {
		cells[m->w * i].score = 0;
		cells[m->w * i].prevs = 0;
	}

	for (unsigned int i = 0; i < m->w; i++) {
		cells[i].score = 0;
		cells[i].prevs = 0;
	}

	m->cells = cells;

	return m;
}

void swFillMat(struct matrix *mat, struct cost *cost, char *s1, char *s2) {
	unsigned int h = mat->h;
	unsigned int w = mat->w;
	for (unsigned int i =1; i < mat->h; i++){
		for (unsigned int j = 1; j < mat->w; j++){
			double score = max (mat->cells[j-1+ w*(i-1)].score + cost->subst(s1[i-1], s2[j-1]),
			 mat->cells[j+ w*(i-1)].score + cost->indelOpen,
					mat->cells[j-1+ w*(i)].score + cost->indelOpen, 0 );
			mat->cells[j+w*i].score = score;
			mat->cells[j+w*i].prevs = 0;
			if (score == mat->cells[j-1+ w*(i-1)].score + cost->subst(s1[i-1], s2[j-1])){
				mat->cells[j+w*i].prevs+=1;
			}
			if (score ==  mat->cells[j+ w*(i-1)].score + cost->indelOpen){
				mat->cells[j+w*i].prevs+=4;
			}
			if (score == mat->cells[j-1+ w*(i)].score + cost->indelOpen){
				mat->cells[j+w*i].prevs+=2;
			}

		}
	}
	printf("\n");
}

void swFreeMat(struct matrix *mat){
	free(mat->cells);
	free(mat);
}

void swPrintMat(struct matrix *mat){
	for (unsigned int i =0; i < mat->h; i++){
		for (unsigned int j = 0; j < mat->w; j++){
			struct cell c = mat->cells[mat->w*i +j];
			if (c.prevs&1){
				printf("d");
			}
			if (c.prevs&2){
				printf("l");
			}
			if(c.prevs&4){
				printf("t");
			}

			printf("%.0f ", c.score);
		}
		printf("\n");
	}
}
