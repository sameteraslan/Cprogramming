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
	srand(time(NULL)); 
	int fd1;
	char * pipeline = "/tmp/pipeline";
	mkfifo(pipeline, 0666);
	int r;
	char rx[12];

	r = rand() % 6; // 0-5
	if (r <= 2) {
	    sprintf(rx, "sat%d", r);  
	} else {
	    sprintf(rx, "sut%d", r % 3);
	}
	fd1 = open(pipeline, O_WRONLY);
	write(fd1, rx, strlen(rx) + 1);
	close(fd1);
	return 0;
}
