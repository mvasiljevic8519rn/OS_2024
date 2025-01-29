#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

#define MAX_WORD_LEN 64 
#define LETTERS 26 		


struct scannedFile { 		
    char fileName[256];	 
    long int timeMod;
};

struct scannedFile scannedFile[100];

extern pthread_mutex_t xLock;
extern void trieAddWord(char *word);
extern char prefiks[MAX_WORD_LEN];


int k = 0;

void *scannerWork(void *args)
{
	DIR *folder; FILE *f;
	char *c = ((char*)args);
	char dirpath[128] = "./";
	struct dirent *entry;
	struct stat filestat;
	
	strcat(dirpath, c);
	strcat(dirpath, "/");

	folder = opendir(dirpath);	
    if(folder == NULL){
		perror("Unable to read directory");
		return(0);
    }
	
	while(1){

		while( (entry=readdir(folder)) ){
			
			if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
				continue;

			char filepath[128];
			strcpy(filepath, dirpath);
			strcat(filepath, entry->d_name);
			
			f = fopen(filepath, "r");
			int fd = fileno(f);
			if(fstat(fd, &filestat) == -1){
				printf("greska\n");
				continue;
			}
			///////////////////////
			//LOCK
			///////////////////////
			pthread_mutex_lock(&xLock);

				int flag=0;
				for(int i=0 ; i<k ; i++){
					if((strcmp(scannedFile[i].fileName, entry->d_name) == 0) && (scannedFile[i].timeMod == filestat.st_mtime)){
						flag=1;
						fclose(f); 
						break;
					}
				}
				if(flag){
					///////////////////////
					//UN-LOCK
					///////////////////////
					pthread_mutex_unlock(&xLock);
					continue;	
				}
				strncpy(scannedFile[k].fileName, entry->d_name, 30);
				scannedFile[k++].timeMod = filestat.st_mtime;
	
			pthread_mutex_unlock(&xLock);

			///////////////////////
			//UN-LOCK
			///////////////////////
			char word[MAX_WORD_LEN], c;
			int i=0, wordFlag=1;
			while((c = fgetc(f)) != EOF){	
				if(c == ' ' || c == '\n' || c == '\t' || i > MAX_WORD_LEN){						
					
					if(wordFlag && strlen(word) > 1)
						trieAddWord(word);
					
					wordFlag = 1, i = 0;
					memset(word, 0, MAX_WORD_LEN);
					continue;
				}
				if(!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'))
					wordFlag = 0;
				if(c >= 'A' && c <= 'Z')
					c = c + ('a'-'A');		
				word[i++] = c;					
			}
			fclose(f);	
		}

	sleep(5);
	closedir(folder);
	folder = opendir(dirpath);
	}
}


