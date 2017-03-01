#include <stdint.h>
#include <string.h>

#include "mem.h"
#include "swCalc.h"

struct matrix *swInitMat(char *s1, char *s2) {
	int len_s1 = strlen(s1);
	int len_s2 = strlen(s2);

	struct cell *cells = mallocOrDie((sizeof(double) + sizeof(uint8_t))*(len_s1 + 1) * (len_s2 + 1), "malloc died");
	for (int i = 0; i < len_s1 + 1; i++) {
		cells[i].score = 0;
		cells[i].prevs = 0;
		cells[len_s2 * i].score = 0;
		cells[len_s2 * i].prevs = 0;
	}

	struct matrix *m = mallocOrDie(sizeof(int) * 2 + (len_s1 + 1) * (len_s2 + 1), "malloc died a second time");
	m->w = len_s2;
	m->h = len_s1;
	m->cells = cells;

	return m;
} 