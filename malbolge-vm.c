#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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

typedef unsigned short ushort;

/* ushort >= 2 ^ 16 == 65536 > 59049 = 3 ^ 10 == malbolge register */
ushort a = 0, c = 0, d = 0;	/*	registers	*/
ushort mm[MEM_SIZE];		/*	main memory	*/

char crz_trit[3][3] = {
	{ 1, 0, 0 },
	{ 1, 0, 2 },
	{ 2, 2, 1 }
};

ushort
crz(ushort a, ushort b)
{
	ushort c = 0, i;
	for (i = 1; i < MEM_SIZE; i *= 3) {
		c += crz_trit[a % 3][b % 3] * i;
		a /= 3;
		b /= 3;
	}
	return c;
}

int
load(FILE *f)
{
	ushort i;
	char c;
	for (i = 0; i < MEM_SIZE;) {
		if (fread(&c, sizeof(char), 1, f) <= 0)
			break;
		if (isspace(c))
			continue;
		switch((c + i) % 94) {
		case JMP:
		case OUT:
		case IN:
		case ROT:
		case MOV:
		case CRZ:
		case NOP:
		case END:
			mm[i++] = c;
			continue;
		default:
			printf("invalid input program: %d - %d - %c\n", i, c, c);
			return 1;
		}
	}
	if (i == 0)
		mm[0] = 1;
	if (i == 1)
		mm[1] = crz(0, mm[1]);
	for (i = (i < 2) ? 2 : i; i < MEM_SIZE; i++)
		mm[i] = crz(mm[i - 2], mm[i - 1]);
	return 0;
}

void
exec_inst(void)
{
	int ch;
	for (;;) {
		if (!isgraph(mm[c]))
			return;
		switch((c + mm[c]) % 94) {
		case JMP:
			c = mm[d];
			break;
		case OUT:
			putc(a, stdout);
			break;
		case IN:
			ch = getc(stdin);
			a = (ch == EOF) ? MEM_SIZE - 1 : ch;
			break;
		case ROT:
			a = mm[d] = mm[d] / 3 + (mm[d] % 3) * (MEM_SIZE / 3);
			break;
		case MOV:
			d = mm[d];
			break;
		case CRZ:
			a = mm[d] = crz(mm[d], a);
			break;
		case END:
			exit(0);
		}

		mm[c] = "5z]&gqtyfr$(we4{WP)H-Zn,[%\\3dL+Q;>U!pJS72FhOA1CB6v^=I"
			"_0/8|jsb9m<.TVac`uY*MK'X~xDl}REokN:#?G\"i@"[mm[c]-33];

		c = (c + 1) % MEM_SIZE;
		d = (d + 1) % MEM_SIZE;
	}
}

int
main(int argc, char **argv)
{
	FILE *f;
	if (argc != 2) {
		fprintf(stderr, "usage:  %s [FILE]\n", argv[0]);
		return 1;
	}
	if (!(f = fopen(argv[1], "r"))) {
		fprintf(stderr, "%s: No such file or directory\n", argv[1]);
		return 2;
	}
	if (load(f))
		return 3;
	fclose(f);
	exec_inst();
	return 0;
}

