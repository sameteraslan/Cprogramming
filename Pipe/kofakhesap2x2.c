#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
int main(int args, char** argv, char ** envp)
{
	int fd1;
	char * pipeline = "/tmp/kofaktor_pipe";
	mkfifo(pipeline, 0777);
	int matrix[2][2];
	int result;
	fd1 = open(pipeline, O_RDONLY);
	read(fd1, matrix, 5*sizeof(int));
	close(fd1);
	//printf("temp:\n%d , %d\n%d , %d\n", matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]);
	result = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
	//printf("result in kofaktor: %d\n", result);
	fd1 = open(pipeline, O_WRONLY);
	write(fd1, &result, sizeof(int));
	close(fd1);
	
	return 0;
}
