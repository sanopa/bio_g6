#include "swOut.h"

void printBestAlis(struct matrix *mat, struct cost *cost, char *s1, char *s2){
	unsigned int h = mat->h;
	unsigned int w = mat->w;
	double scoreMax = 0;
	unsigned int i_max = 0;
	unsigned int j_max = 0;
	for (unsigned int i =1; i < mat->h; i++){
		for (unsigned int j = 1; j < mat->w; j++){
			if (mat->cells[w*i+j].score > scoreMax){
				scoreMax = mat->cells[w*i+j].score ; 
				i_max = i;
				j_max = j;
			}
		}
	}


}