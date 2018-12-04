/**
* Created by Abdulsamet ERASLAN - 2018
* Fatih Sultan Mehmet Vakif University Computer Engineering
* Operating Systems Second Poject
**/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <termios.h>
#include <assert.h>

/**
* Bu fonksiyon fork ile satsut programından 
* seçilen satir ya da sutun numarasını pipe yöntemi ile okumaktadır.
**/
char* readRawCol(void) {
	pid_t pid;
	int child_process;
	int fd;
	char *arr1 = malloc(sizeof(char) * 50);
	char * pipeline = "/tmp/pipeline";
        mkfifo(pipeline, 0666);

	pid = fork();

	if (pid == 0) { // Child Process
		child_process = execve("satsut", NULL, NULL);
		perror("Beklenmeyen Hata");
	}
	else if (pid < 0) { // Forking Error
		perror("hata lutfen yeniden baslatin.");
	}
	else { // Parent Process
		//wait(&child_process);
		sleep(0.3);
		fd = open(pipeline, O_RDONLY);
		read(fd, arr1, 4);
		printf("satsut: %s\n", arr1);
		close(fd);
		return arr1;
	}
}

/**
* Parametre olarak aldığı 2x2 matrisi fork ile oluşturulan çocuk process ile kofaktor programına göndererek
* kofaktor programında hesaplanan değeri okumaktadır.
**/
int kofaktorAl(int matrix[2][2]) {
	pid_t pid;
	int child_process;
	int fd;
	const char * pipeline = "/tmp/kofaktor_pipe";
	int result;
        mkfifo(pipeline, 0666);
	pid = fork();
	if (pid == 0) {  // Child Process
		sleep(0.2);
		child_process = execve("kofaktor", NULL, NULL);
		perror("Beklenmeyen Hata");
	} else if (pid < 0) { // Forking Error
		perror("hata lutfen yeniden baslatin.");
	} else {  // Parent Process
		
		fd = open(pipeline, O_WRONLY);
		write(fd, matrix, 4 * sizeof(int));
		close(fd);
		wait(&child_process);
		//sleep(2);
		fd = open(pipeline, O_RDONLY);
		read(fd, &result, sizeof(int));
		close(fd);
		//printf("dosyadan okunan result: %d\n", result);
		return result;
	}
}

/**
* Verilen ilk parametre taban, ikinci parametre ust olmak üzere
* taban ^ ust işlemini hesaplar ve sonucu dondurur.
**/
int pow(int alt, int ust) {
	int i;
	int sonuc = 1;
	for (i = 0; i < ust; i++) {
		sonuc = sonuc * alt;
	}
	return sonuc;
}

/**
* Enter'a basılmadan her harf girildiğinde çalışan fonksiyondur.
* Alıntı : https://ubuntuforums.org/showthread.php?t=554845
**/
int getch(void) {
      int c=0;

      struct termios org_opts, new_opts;
      int res=0;
          //-----  store old settings -----------
      res=tcgetattr(STDIN_FILENO, &org_opts);
      assert(res==0);
          //---- set new terminal parms --------
      memcpy(&new_opts, &org_opts, sizeof(new_opts));
      new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
      tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
      c=getchar();
          //------  restore old settings ---------
      res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
      assert(res==0);
      return(c);
}

/**
* Programın ilk aşamasında rastgele 3x3 matris oluşturulmuştur.
* matris oluşturulduktan sonra readRawCol() fonksiyonu ile hangi satir ya da sutuna göre
* kofaktor alınacağı belirlenir.
* kofakhesap(int matrix[2][2]) fonksiyonu verilen 2x2 matrisi hesaplar ve sonucu dondurur.
**/
int main(void)
{ 
    //matris oluşturulma kısmı
    int matrix[3][3];
    int i, j, m;
    srand(time(NULL));
    int satir_sayac = 0, sutun_sayac = 0;
    for	(i = 0; i < 3; i++) {
	for (j = 0; j < 3; j++) {
	    matrix[i][j] = rand() % 6;
	}
    }
    printf("matris:\n%d , %d, %d\n%d , %d, %d\n%d , %d, %d\n", matrix[0][0], matrix[0][1], matrix[0][2], 
								matrix[1][0], matrix[1][1], matrix[1][2],
								matrix[2][0], matrix[2][1], matrix[2][2]);
    int k;
    char * detV = malloc(sizeof(char) * 1024);
    int sonuc;
    int temp[2][2];
    int kofak_sonuc;
    char c;
    while(1) {
	sonuc = 0;
	kofak_sonuc = 0;
	strcpy(detV, readRawCol());
	k = detV[3] - '0';
	if (detV[1] == 'a') {
		for (j = 0; j < 3; j++) {
			satir_sayac = 0; 
			sutun_sayac = 0;
			for (i = 0; i < 3; i++) {
				if (i == k) continue;
				for (m = 0; m < 3; m++) {
					if (m == j) continue;
					temp[satir_sayac][sutun_sayac] = matrix[i][m];
					sutun_sayac++;
				}
				sutun_sayac = 0;
				satir_sayac++;
			}
			kofak_sonuc = kofaktorAl(temp);
			sonuc += pow(-1, k + j) * matrix[k][j] * kofak_sonuc;
		}
	}
	else if (detV[1] == 'u') {
		for (j = 0; j < 3; j++) {
			satir_sayac = 0; 
			sutun_sayac = 0;
			for (i = 0; i < 3; i++) {
				if (i == j) continue;
				for (m = 0; m < 3; m++) {
					if (m == k) continue;
					temp[satir_sayac][sutun_sayac] = matrix[i][m];
					sutun_sayac++;
				}
				satir_sayac++;
				sutun_sayac = 0;
			}
			//printf("temp:\n%d , %d\n%d , %d\n", temp[0][0], temp[0][1], temp[1][0], temp[1][1]);
			kofak_sonuc = kofaktorAl(temp);
			//printf("kofaktor sonucu: %d\n", kofak_sonuc);
			sonuc += pow(-1, k + j) * matrix[j][k] * kofak_sonuc;
			//printf("sonuc for sut: %d\n", sonuc);
			//sleep(0.5);
		}
	}
	printf("sonuc : %d\n", sonuc);

	printf("Devam etmek için herhangi bir tuşa basınız. Çıkmak için (n)\n");
	c = getch();
	if (c == 'n') break;
    }
    return 0;
}
