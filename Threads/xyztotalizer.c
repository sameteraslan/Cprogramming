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
#include <sys/wait.h>
#include <time.h>
#include <termios.h>
#include <assert.h>

//global değişkenler
pthread_mutex_t lockx;
pthread_mutex_t locky;
pthread_mutex_t lockz;
int linenum = 1;
int readcount;
int resultx, resulty, resultz;

// Eğer matrix[0] = 0 ise threadx, 1 ise thready, 2 ise threadz çalışacak şekilde programlanmıştır.
int matrix[2]; // 0 -> linenumber, 1 -> thread_name;


/**
* Kullanıcının satir sayisi girmesi için oluşturulmuştur.
* Parametre almaz. girilen değeri döndürür.
**/
char* readLine(void) {
	int c;
        int index = 0;
	char* line = malloc(sizeof(char) * 1024);
	while(1) {
		c = getchar();
		if (c == '\n' || c == EOF) {
			line[index] = '\0';
			return line;
		} else {
			line[index] = c;
		}
		index++;
	}
}

/**
* Bu fonksiyon x threadi için oluşturulmuş olup named pipe yapısı
* kullanılarak numberreader.c programının okuyacağı 2 elemanlı matris göndermektedir.
* Gönderdikten sonra numberreader.c programında dosyadan okunan değer tekrar named pipe yapısıyla
* okunur ve resultx değişkenine atanir.
* matrix[0]: hangi thread olduğunu gösterir. matrix[1]: satir sayisini alir.
**/
void *x() // thread x için
{

    while(linenum < readcount - 1)
    {       
	    //x threadi tekrar çalışmaması için lock yapıldı.
	    pthread_mutex_lock(&lockx);
	    int fd;
	    char * pipeline = "/tmp/mypipe";
	    mkfifo(pipeline, 0666);
	    matrix[0] = 0;
	    matrix[1] = linenum;
	    fd = open(pipeline, O_WRONLY);
	    write(fd, matrix, 2 * sizeof(int));
	    close(fd);
	    linenum = linenum + 1;
	    usleep( 1000 );
	    fd = open(pipeline, O_RDONLY);
	    read(fd, &resultx, sizeof(int)); 
    	    close(fd);	
	    //x den sonra y threadi çalışacağı için kilidi kaldırıldı.
	    pthread_mutex_unlock(&locky);
    }
}

/**
* Bu fonksiyon y threadi için oluşturulmuş olup named pipe yapısı
* kullanılarak numberreader.c programının okuyacağı 2 elemanlı matris göndermektedir.
* Gönderdikten sonra numberreader.c programında dosyadan okunan değer tekrar named pipe yapısıyla
* okunur ve resulty değişkenine atanir.
* matrix[0]: hangi thread olduğunu gösterir. matrix[1]: satir sayisini alir.
**/
void *y() // thready için
{
    while(linenum < readcount)
    {
	    //y threadi tekrar çalışmaması için lock yapıldı.
	    pthread_mutex_lock(&locky);
	    int fd;
	    char * pipeline = "/tmp/mypipe";
	    mkfifo(pipeline, 0666);
	    matrix[0] = 1;
	    matrix[1] = linenum;
	    fd = open(pipeline, O_WRONLY);
	    write(fd, matrix, 2 * sizeof(int));
	    close(fd);
	    linenum = linenum + 1;
	    usleep( 1000 );
	    fd = open(pipeline, O_RDONLY);
	    read(fd, &resulty, sizeof(int)); 
    	    close(fd);	
	    //y den sonra z threadi çalışacağı için kilidi kaldırıldı.
	    pthread_mutex_unlock(&lockz);
    }
}

/**
* Bu fonksiyon z threadi için oluşturulmuş olup named pipe yapısı
* kullanılarak numberreader.c programının okuyacağı 2 elemanlı matris göndermektedir.
* Gönderdikten sonra numberreader.c programında dosyadan okunan değer tekrar named pipe yapısıyla
* okunur ve resultz değişkenine atanir.
* matrix[0]: hangi thread olduğunu gösterir. matrix[1]: satir sayisini alir.
**/
void *z() // thread z için
{
    while(linenum < readcount)
    {       
	    //z threadi tekrar çalışmaması için lock yapıldı.
	    pthread_mutex_lock(&lockz);
	    int fd;
	    char * pipeline = "/tmp/mypipe";
	    mkfifo(pipeline, 0666);
	    matrix[0] = 2;
	    matrix[1] = linenum;
	    fd = open(pipeline, O_WRONLY);
	    write(fd, matrix, 2 * sizeof(int));
	    close(fd);
	    linenum = linenum + 1;
	    usleep( 1000 );
	    fd = open(pipeline, O_RDONLY);
	    read(fd, &resultz, sizeof(int)); 
    	    close(fd);	
	    printf("x + y + z = %d\n", (resultx + resulty + resultz));
	    //z den sonra x threadi çalışacağı için kilidi kaldırıldı.
	    pthread_mutex_unlock(&lockx);
    }
}

int main()
{
    //mutex için bir başlangıç bölgesi oluşturuldu.
    pthread_mutex_init(&lockx, NULL);
    pthread_mutex_init(&locky, NULL);
    pthread_mutex_init(&lockz, NULL);

    //kritik bölgeye girilmeden önce thread kilitlenlendi.
    pthread_mutex_lock(&lockz);
    pthread_mutex_lock(&locky);

    char *line_count;
    printf("Lutfen dosyadan okunacak satir sayisini giriniz: ");
    line_count = readLine();
    readcount = atoi(line_count);

    pthread_t threadx;
    pthread_t thready;
    pthread_t threadz;

    void* status;
    //threadler oluşturuldu.
    pthread_create(&threadx,NULL,x,NULL);
    sleep(0.1);
    pthread_create(&thready,NULL,y,NULL);
    sleep(0.1);
    pthread_create(&threadz,NULL,z,NULL);
    sleep(0.1);
    //threading sonlanmasını bekliyor.
    pthread_join(threadx,&status);
    pthread_join(thready,&status);
    pthread_join(threadz,&status);

    pthread_mutex_destroy(&lockx); // olmasa olabilir.
    pthread_mutex_destroy(&locky); // olmasa olabilir.
    pthread_mutex_destroy(&lockz); // olmasa olabilir.

    return 0;
}
