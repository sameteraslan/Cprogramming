/**
* Created by Abdulsamet ERASLAN - 2018
* Fatih Sultan Mehmet Vakif University Computer Engineering
* Operating Systems First Project
**/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
* Kullanıcının komut girmesi için gereken fonksiyondur.
*
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
* komutu parçalarına ayırır. char** dizisi döndürür. ilk eleman komutun kendisidir.
**/
#define SPLIT " \t\r\n\a"
char** parseLine(char* line) {
	int index = 0;
	char *splitted = strtok(line, SPLIT);
	char **splitted2 = malloc(16 * sizeof(char*));
	while(splitted != NULL) {
		splitted2[index] = splitted;
		splitted = strtok(NULL, SPLIT);
		index++;
	}
	splitted2[index] = NULL;
	return splitted2;
}

/**
* parseProcess fonksiyonu kullanıcıdan gelen metni & ifadesine göre parçalar. Parçalanmış halini döndürür.
**/
#define DELIM "&\n"
char** parseProcess(char* line) {
	int index = 0;
	char *splitted = strtok(line, DELIM);
	char **splitted2 = malloc(16 * sizeof(char*));
	while(splitted != NULL) {
		splitted2[index] = splitted;
		splitted = strtok(NULL, DELIM);
		index++;
	}
	splitted2[index] = NULL;
	return splitted2;
}

/**
* Parametre olarak gelen args char** dizisinde ilk indexte yer alan komuta göre execve fonksiyonunu çalıştırmadan önce
* fork yapılır ve child processte bunlar yapılır. Eğer kullanıcı exit yazarsa program sonlanır.
**/
int executeLine(char** args) {
	pid_t pid;
	int child_process;
	
	pid = fork();
	if (pid == 0) // Child Process
	{

		if (strcmp(args[0], "div") == 0)
		{
			child_process = execve(args[0], args, NULL);
		} 
		else if (strcmp(args[0], "mul") == 0)
		{
			child_process = execve(args[0], args, NULL);
		}
		else if (strcmp(args[0], "cat") == 0)
		{	
			child_process = execve("/bin/cat", args, NULL);
		}
		else if (strcmp(args[0], "rakam") == 0)
		{	
			child_process = execve(args[0], args, NULL);
		} 
		else if (strcmp(args[0], "exit") != 0)
		{
			printf("Hata! Asagidaki komutlari kullanmalisin:\n -div\n -mul\n -exit\n");
		}
	} 
	else if (pid < 0) // Forking Error
	{
		printf("Forking Error");
		return -1;
	}
	else // Parent Process
	{	
		if (strcmp(args[0], "rakam") != 0) {
			wait(&child_process);
		}
		if (strcmp(args[0], "exit") == 0)
		{	
			return -1;
		}
		else if(strcmp(args[0], "clear") == 0)
		{
			system("clear");
			return 1;
		}
		else
		{
			return 1;
		} 
	}
}

/**
* loop() fonksiyonu kullanıcının girdiği metni & ile ayırıp splittedLines char dizisine atar.
* Girilen komut kadar while döngüsü çalışmaktadır.
**/
void loop(void)
{
	char* line;
	char** args;
	int status = 1;
	int i = 0;
	char **splittedLines = malloc(96 * sizeof(char*));
	while(status == 1) {
		printf("my_shell>> ");
		line = readLine();

		splittedLines = parseProcess(line);
		i = 0;
		while (splittedLines[i] != NULL) 
		{	
			args = parseLine(splittedLines[i]);
			status = executeLine(args);
			args = NULL;
			splittedLines[i++] = strtok(NULL, "&");
		}

	}
}

/**
* Bu fonksiyon, programın çalışmaya başladığı fonksiyondur.
* içerisinde loop() fonksiyonu çağrılmıştır.
*
**/
int main(int args, char** argv, char ** envp) {
    loop();
    return 0;
}
