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

/* short >= 2^ 16 == 65536 > 59049 = 3 ^ 10 == malbolge register */
short a = 0, c = 0, d = 0;	/*	registers	*/
short mm[MEM_SIZE];		/*	main memory	*/

int
main(int argc, char **argv)
{
	
	return 0;
}
