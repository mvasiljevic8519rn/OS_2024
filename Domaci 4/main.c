#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include "scanner.h"  // Include scanner.h

#define MAX_WORD_LEN 64 //najveca dozvoljena duzina reci, uz \0
#define LETTERS 26 //broj slova u abecedi i broj dece u trie

#define prefix pthread_mutex_t
#define zakljucajPrefix pthread_mutex_lock
#define odkljucajPrefix pthread_mutex_unlock

char prefiks[MAX_WORD_LEN];
int printFlag = 0;

typedef struct trieNode {
    char c; //slovo
    int endOfWord; //flag za kraj reci
    int subwords; //broj reci u podstablu -1
    int newFlag;    //novi 
    struct trieNode *parent; //roditelj
    struct trieNode *children[LETTERS]; //dete
    pthread_mutex_t prefix;
} trieNode;

typedef struct searchResult {
    int resultCount; //duzina niza
    char **words; //niz stringova, svaki string duzine MAX_WORD_LEN
} searchResult;

struct trieNode *root;
char *ans, *p;

trieNode* createNode(trieNode *parent, char c) {
    struct trieNode *newNode;
    newNode = malloc(sizeof(trieNode));
    newNode->c = c;
    newNode->parent = parent;
    newNode->newFlag = 0;    
    newNode->subwords = 0;
    newNode->endOfWord = 0;
    pthread_mutex_init(&newNode->prefix, NULL);
    int i;
    for(i = 0; i < LETTERS; i++)
        newNode->children[i] = NULL;

    return newNode;
}

void insert(trieNode* node, char *str, int i) {
    if(i < strlen(str)){
        int index = str[i] - 'a';
        
        if(node->children[index] == NULL)
            node->children[index] = createNode(node, str[i]);
        
        zakljucajPrefix(&node->prefix); // mutex_lock
        
        insert(node->children[index], str, i + 1);

        if(node->newFlag == 1){
            node->subwords++;
            node->newFlag = 0;
            if(node->parent != NULL)
                node->parent->newFlag = 1;
            else
                root->newFlag = 1;
        }

        odkljucajPrefix(&node->prefix); // mutex_unlock
        
    } else {
        
        if(node->endOfWord == 1)
            return;
        // nova rec u stablu
        node->parent->newFlag = 1;
        node->endOfWord = 1;
    }
}
//operacija za dodavanje reci
void trieAddWord(char *word) {
    insert(root, word, 0);
    
    if(root->newFlag == 1) {
        if(printFlag == 1 && strlen(prefiks) > 0 && strncmp(prefiks, word, strlen(prefiks)) == 0)
            printf("%s\n", word);
        
        root->newFlag = 0;
    }
}

void traverse(trieNode* node, char *str, int x) {
    int i=0;
    for(i = 0; i < LETTERS; i++) {
        if(node->children[i] == NULL)
            continue;
        if(node->children[i]->endOfWord == 1) {
            str[x] = i + 'a';
            strncpy(ans, str, MAX_WORD_LEN - 1);
            ans[MAX_WORD_LEN - 1] = '\0';
            ans += MAX_WORD_LEN;
        } else
            str[x] = i + 'a';
        
        traverse(node->children[i], str, x + 1);
        str[x] = 0;
    }
}
//operacija za pretragu ; neophodno je proveriti da li se na prefiksu nalazi endOfWord, da bi smo znali da li i tu rec da racunamo
searchResult *trieGetWords(char *prefix) {
    int i = 0;
    int k = 0;
    struct trieNode *tmp = root;

    for(i = 0; i < strlen(prefix); i++) {
        k = prefix[i] - 'a';
        if(tmp->children[k] == NULL)
            return NULL;
        tmp = tmp->children[k];
    }
    
    zakljucajPrefix(&tmp->prefix); // mutex_lock

    struct searchResult *result = malloc(sizeof(searchResult));

    result->resultCount = tmp->subwords;
    if(tmp->endOfWord)
        result->resultCount++;
    
    p = malloc(result->resultCount * (sizeof(char)) * MAX_WORD_LEN);
    ans = p;
    result->words = &p;
    
    // ako je trazeni prefix rec u stablu
    if(tmp->endOfWord) {
        strncpy(ans, prefix, MAX_WORD_LEN - 1);
        ans[MAX_WORD_LEN - 1] = '\0';
        ans += MAX_WORD_LEN;
    }

    char str[MAX_WORD_LEN];
    int x = strlen(prefix);
    strncpy(str, prefix, strlen(prefix));

    traverse(tmp, str, x);
    
    odkljucajPrefix(&tmp->prefix); // mutex_unlock

    return result;
}
//rezultat se dinamicki alocira pri pretrazi, tako da treba da postoji funkcija za oslobadjanje tog rezultata
void trieFreeResult(searchResult *result) {
    free((char*)(*result->words));
}

void removeTrieMutex1(trieNode* node) {
    if(node == NULL)
        return;
    int i;
    for(i = 0; i < 26; i++) {
        pthread_mutex_destroy(&node->prefix);
        removeTrieMutex1(node->children[i]);
    }
}

void removeTrieMutex() {
    removeTrieMutex1(root);
}

void trieInit() {
    root = malloc(sizeof(trieNode));
    root->newFlag = 0;
    root->c = 0;
    root->parent = NULL;
    root->subwords = 0;
    root->endOfWord = 0;
    pthread_mutex_init(&root->prefix, NULL);

    for(int i= 0; i < LETTERS; i++) {
        root->children[i] = NULL;
    }
}

pthread_mutex_t xLock;
pthread_t threads[30];
int i= 0;

int nextLine(void) {
    int rturnLine = fgetc(stdin);
    return rturnLine;
}

int main() {
    trieInit();
    char inputComand[30];
    struct searchResult *result;
    pthread_mutex_init(&xLock, NULL);
    
	printf("Commands _add_,_stop_ prefix: \n");

    while (1) {
        if (fgets(inputComand,sizeof(inputComand), stdin) == NULL) {
            // Handle end of input (Ctrl+D)
            if (feof(stdin)) {
                clearerr(stdin);
                continue;
            }
        }

        // Remove trailing newline character
        inputComand[strcspn(inputComand, "\n")] = '\0';

        if (strncmp("_add_", inputComand, 5) == 0) {
            pthread_create(&threads[i], NULL, scannerWork, (void *)(&inputComand[6]));
            i++;
        } else if (strcmp("_stop_", inputComand) == 0) {
            break;
        } else {
            memset(prefiks, 0, MAX_WORD_LEN);
            int x=0;
            int j=0; 
            for (j = 0; j < strlen(inputComand) && j < MAX_WORD_LEN; x++, j++) {
                if (inputComand[k] == ' ') {
                    memset(prefiks, 0, x);
                    x = -1;
                    continue;
                }
                prefiks[x] = inputComand[j];
            }

            if ((result = trieGetWords(prefiks)) == NULL)
                continue;

            printFlag = 1;

            char *p = *result->words;
            int i=0;
            for (i = 0; i < result->resultCount; i++) {
                printf("%s\n", p);
                p += MAX_WORD_LEN;
            }
            trieFreeResult(result);

            int key;
            while (1) {
                if ((key = nextLine()) == -1) {
                    printFlag = 0;
                    break;
                }
            }
        }
    }

    removeTrieMutex();
    pthread_mutex_destroy(&xLock);

    return 0;
}
