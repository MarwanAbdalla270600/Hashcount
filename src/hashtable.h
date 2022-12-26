
#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <stdbool.h>

typedef struct word {
	char *name;
	unsigned int frequency;
	struct word *next;
} word;


word* insertIntoTable(word **hashtable, unsigned int tablesize, char *word);

void freeTable(word **hashtable, unsigned int tablesize);

bool bucketContainsWord(word *bucket, char *entry);

word* getBucket(word **hashtable, unsigned int tablesize, unsigned int bucket);

void printBucket(word **hashtable, unsigned int tablesize, unsigned int bucket);


void printTable(word **hashtable, unsigned int tablesize);


#endif /* HASHTABLE_H_ */
