#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **args, char **envp)
{
	int i = 0;
	while(1)
	{	
		i++;
		if (args[i] != NULL)
			printf("%s ", args[i]);
		else
			break;
	}
	printf("\n");
}
