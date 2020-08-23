#include <stdio.h>

/* 
 * Malbolge executes on a ternary virtual machine with a machine-width of 10
 * 59049 = 3 ^ 10
 */
#define WIDTH 10
#define MEM_SIZE 59049
#define MAGIC 94

/* instructions */
#define JMP 4
#define OUT 5
#define IN  23
#define ROT 39
#define MOV 40
#define CRZ 62
#define NOP 68
#define END 81

/* short >= 2 ^ 16 == 65536 > 59049 = 3 ^ 10 == malbolge register */
short a = 0, c = 0, d = 0;	/*	registers	*/
short mm[MEM_SIZE];		/*	main memory	*/

char crz_trit[3][3] = {
	{ 1, 0, 0 },
	{ 1, 0, 2 },
	{ 2, 2, 1 }
};

short
crz(short a, short b)
{
	short c = 0, i;
	for (i = 1; i < MEM_SIZE; i *= 3) {
		c += crz_trit[a % 3][b % 3] * i;
		a /= 3;
		b /= 3;
	}
	return c;
}

void
load(FILE *f)
{
	short i;
	for (i = 0; i < MEM_SIZE; i++) {
		if (!fread(mm + i, sizeof char, 1, f))
			break;
	}
	for (i = i < 2 ? 2 : i; i < MEM_SIZE; i++)
		mm[i] = crz(mm[i - 2], mm[i - 1]);
}

int
main(int argc, char **argv)
{
	FILE *f;
	if (argc != 2) {
		perror("usage:  malbolge-vm FILE\n");
		return 1;
	}
	f = fopen(argv[1], "r");
	if (!f) {
		printf("%s: No such file or directory\n", argv[1]);
		return 2;
	}
	load(f);

	return 0;
}
