#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **args, char **envp)
{
	int x = atoi(args[1]);
	switch(x) {
		case 0:
			printf("%d >> sifir\n", x);
			break;
		case 1:
			printf("%d >> bir\n", x);
			break;
		case 2:
			printf("%d >> iki\n", x);
			break;
		case 3:
			printf("%d >> uc\n", x);
			break;
		case 4:
			printf("%d >> dort\n", x);
			break;
		case 5:
			printf("%d >> bes\n", x);
			break;
		case 6:
			printf("%d >> alti\n", x);
			break;
		case 7:
			printf("%d >> yedi\n", x);
			break;
		case 8:
			printf("%d >> sekiz\n", x);
			break;
		case 9:	
			printf("%d >> dokuz\n", x);
			break;
		default:
			printf("HATA\n");

	}
    return 0;
}
