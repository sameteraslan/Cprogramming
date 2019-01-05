/**
* Created by Abdulsamet ERASLAN - 2018
* Fatih Sultan Mehmet Vakif University Computer Engineering
* Operating Systems Third Project
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include <assert.h>
// Bu Kod https://stackoverflow.com/questions/3501338/c-read-file-line-by-line sitesinden alınmıştır (Düzenleme yapıldı).
int main(void)
{
    const char * pipeline = "/tmp/mypipe";
    mkfifo(pipeline, 0666);
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t reading;
    int i;
    int read_count[2];
    int counter = 0;
    int sonuc;
    int fd1;
    while (1)
    {
	    line = NULL;
	    len = 0;
	    reading = NULL;
	    sonuc = NULL;
	    counter = 0;
	    fd1 = open(pipeline, O_RDONLY);
	    read(fd1, read_count, 2 * sizeof(int));
	    close(fd1);
	    // Burada ana programdan gelen matrisin hangi threadi gönderdiği bulunur.
	    if (read_count[0] == 0)
	    {
		printf("x = ");
	    }
	    else if (read_count[0] == 1)
	    {
		printf("y = ");
	    }
	    else if (read_count[0] == 2)
	    {
		printf("z = ");
	    }
	    else
	    {
		printf("HATA! Lutfen yeniden baslatin %d\n", read_count[0]);
		return;
	    }
	    //Dosya readonly olarak açıldı.
	    fp = fopen("numbers.txt", "r");
	    
    	    // While döngüsü numbers.txt dosoyasında satir olduğu sürece
	    // istenilen satir sayisina gelene kadar okuma yapar.
	    // İstenilen satir sayisindan yapilan okuma named pipe ile yazilir ve ana program bu yaziyi okur.
	    while ((reading = getline(&line, &len, fp)) != -1)
	    {
		counter++;
		if (counter == read_count[1])
		{
			sonuc = atoi(line);
			printf("%d\n", sonuc);
			fd1 = open(pipeline, O_WRONLY);
	    		write(fd1, &sonuc, sizeof(int));
	    		close(fd1);
			break;
		}	    
	    }
	    //dosya kapatildi.
	    fclose(fp);
    }
    return 0;
}
