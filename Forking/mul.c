#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **args, char **envp)
{

	if (strcmp(args[0], "mul") == 0)
	{
		int x = atoi(args[1]);
		int y = atoi(args[2]);
		printf("%d * %d = %d\n", x, y, x * y);
	}
	else
	{
		printf("Beklenmeyen hata! Lutfen tekrar deneyin.\n");
	
	}

    return 0;
}
