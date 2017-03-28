#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "mem.h"
#include "gotohCalc.h"
#include "swCost.h"
#include <assert.h>

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

struct matrix *gotohInitMat(char *s1, char *s2) {
	int len_s1 = strlen(s1);
	int len_s2 = strlen(s2);


	struct matrix *m = mallocOrDie(sizeof(struct matrix), "malloc died a second time");
	m->w = len_s2 + 1;
	m->h = len_s1 + 1;

	struct cell *cells = mallocOrDie(sizeof(struct cell)*(len_s1 + 1) * (len_s2 + 1), "malloc died");
	for (unsigned int i = 0; i < m->h; i++) {
		cells[m->w * i].scoreH = -1;
		cells[m->w * i].prevsH = 0;
    cells[m->w * i].scoreV = -1;
		cells[m->w * i].prevsV = 0;
    cells[m->w * i].scoreD = 0;
		cells[m->w * i].prevsD = 0;
	}

	for (unsigned int i = 0; i < m->w; i++) {
    cells[m->w * i].scoreH = -1;
		cells[m->w * i].prevsH = 0;
    cells[m->w * i].scoreV = -1;
		cells[m->w * i].prevsV = 0;
    cells[m->w * i].scoreD = 0;
		cells[m->w * i].prevsD = 0;
  }

	m->cells = cells;

	return m;
}

void gotohFillMat(struct matrix *mat, struct cost *cost, char *s1, char *s2) {
	unsigned int h = mat->h;
	unsigned int w = mat->w;
	for (unsigned int i =1; i < h; i++){
		for (unsigned int j = 1; j < w; j++){
      mat->cells[j+w*i].scoreD = max (mat->cells[j-1+ w*(i-1)].scoreD + cost->subst(s1[i-1], s2[j-1]),
        mat->cells[j-1+ w*(i-1)].scoreV + cost->subst(s1[i-1], s2[j-1]),
        mat->cells[j-1+ w*(i-1)].scoreH + cost->subst(s1[i-1], s2[j-1]), 0 );

      mat->cells[j+w*i].scoreV = max (mat->cells[j+ w*(i-1)].scoreD + cost->indelOpen,
        mat->cells[j+ w*(i-1)].scoreV + cost->indelExtend,
        mat->cells[j+ w*(i-1)].scoreH + cost->indelOpen, 0 );

      mat->cells[j+w*i].scoreH = max (mat->cells[j-1+ w*(i)].scoreD + cost->indelOpen,
        mat->cells[j-1+ w*(i)].scoreV + cost->indelOpen,
        mat->cells[j-1+ w*(i)].scoreH + cost->indelExtend, 0 );


        mat->cells[j+w*i].prevsD=0;
        mat->cells[j+w*i].prevsV=0;
        mat->cells[j+w*i].prevsH=0;


        //prevsD. Le précédent est donc forcément en i-1, j-1
			if (mat->cells[j+w*i].scoreD == mat->cells[j-1+ w*(i-1)].scoreD + cost->subst(s1[i-1], s2[j-1]) ){
				mat->cells[j+w*i].prevsD+=1;  //on vient de D
			}
			if (mat->cells[j+w*i].scoreD == mat->cells[j-1+ w*(i-1)].scoreV + cost->subst(s1[i-1], s2[j-1])){
				mat->cells[j+w*i].prevsD+=4; //on vient de V
			}
			if (mat->cells[j+w*i].scoreD == mat->cells[j-1+ w*(i-1)].scoreH + cost->subst(s1[i-1], s2[j-1])){
				mat->cells[j+w*i].prevsD+=2; //on vient de H
			}

      //prevsV. precedent en i-1, j
      if (mat->cells[j+w*i].scoreV == mat->cells[j+ w*(i-1)].scoreD + cost->indelOpen){
        mat->cells[j+w*i].prevsV+=1;  //on vient de D
      }
      if (mat->cells[j+w*i].scoreV == mat->cells[j+ w*(i-1)].scoreV + cost->indelExtend){
        mat->cells[j+w*i].prevsV+=4;  //on vient de V
      }
      if (mat->cells[j+w*i].scoreV == mat->cells[j+ w*(i-1)].scoreH + cost->indelOpen){
        mat->cells[j+w*i].prevsV+=2;  //on vient de H
      }

      //prevsH. precedent en i, j-1
      if (mat->cells[j+w*i].scoreH == mat->cells[j-1+ w*(i)].scoreD + cost->indelOpen){
        mat->cells[j+w*i].prevsH+=1;  //on vient de D
      }
      if (mat->cells[j+w*i].scoreH == mat->cells[j-1+ w*(i)].scoreV + cost->indelOpen){
        mat->cells[j+w*i].prevsH+=4;  //on vient de V
      }
      if (mat->cells[j+w*i].scoreH == mat->cells[j-1+ w*(i)].scoreH + cost->indelExtend){
        mat->cells[j+w*i].prevsH+=2;  //on vient de H
      }
		}
	}
}

void gotohFreeMat(struct matrix *mat){
	free(mat->cells);
	free(mat);
}

void gotohPrintMat(struct matrix *mat){
	// for (unsigned int i =0; i < mat->h; i++){
	// 	for (unsigned int j = 0; j < mat->w; j++){
	// 		struct cell c = mat->cells[mat->w*i +j];
	// 		if (c.prevs&1){
	// 			printf("d");
	// 		}
	// 		if (c.prevs&2){
	// 			printf("l");
	// 		}
	// 		if(c.prevs&4){
	// 			printf("t");
	// 		}
  //
	// 		printf("%.0f ", c.score);
	// 	}
	// 	printf("\n");
	// }
}
