#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

#define LETTERS 26 		

#define MAX_WORD_LEN 60

#define prefix 			pthread_mutex_t
#define uzmi_prefix		pthread_mutex_lock
#define spusti_prefix	pthread_mutex_unlock

struct trieNode *root;


typedef struct rezultati{
    int resultCount;
    chat **reci;
}rezultati;

typedef struct trieNode{
    char c;
    int krajReci;
    int subself;
    int notifikacija;
    struct trieNode *parent;
    struct trieNode *children[LETTERS];
    pthread_mutex_t prefix;
}

trieNode* 
createTrieNode(char c,trieNode *parent){
    int i=0;

    struct trieNode *newNode;
    newNode = malloc(sizeof(trieNode));
    newNode ->c = c;
    newNode ->parent = parent;
    newNode ->krajReci = 0;
    newNode ->podRec = 0;
    notifikacija ->notifikacija = 0;
    pthread_mutex_init(&newNode->prefix,NULL);

    for(i=0;i<LETTERS;i++){
        newNode ->children[i]=NULL;
    } 


    return newNode;
}

void
trieFreeResults(rezultati *rezultat){
    free((char*)(*rezultat->reci))
}

void
trieInit(){
    root = malloc(sizeof(trieNode));
    root ->c = c;
    root ->parent = NULL;
    root ->krajReci = 0;
    root ->podRec = 0;
    root ->notifikacija = 0;
    pthread_mutex_init(&root->prefix,NULL);

    for(i=0;i<LETTERS;i++){
        root ->children[i]=NULL;
    } 

}