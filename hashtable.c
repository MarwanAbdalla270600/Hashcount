#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct word {
	char *content;
	unsigned int frequency;
	struct word *next;
} word;


unsigned int hash(char *content, unsigned int tablesize) {
	int length = strlen(content);
	unsigned int hashvalue = 0;
	for (int i = 0; i < length; i++) {
		hashvalue += content[i];
	}
	hashvalue %= tablesize;
	return hashvalue;
}

static word* getWordFromString(char *word) {
	struct word *pointer = calloc(1, sizeof(word));
	pointer->content = word;
	pointer->frequency = 1;
	pointer->next = NULL;
	return pointer;
}

static void freeList(word *list) {
	while (list != NULL) {
		word *tmp = list->next;
		free(list);
		list = tmp;
	}
}

void freeTable(word **hashtable, unsigned int tablesize) {
	for (int i = 0; i < tablesize; i++) {
		freeList(hashtable[i]);
		hashtable[i] = NULL;
	}
}

static void printLinkedList(word *list) {
	unsigned int counter = 1;
	while (list->next != NULL) {
		if (list->frequency >= 2)
			printf("%s(%u) - ", list->content, list->frequency);
		else
			printf("%s - ", list->content);
		list = list->next;
		if(counter%10 == 0) {
			printf("\n\t\t\t");
		}
		counter++;
	}
	printf("%s\n", list->content);   //letzes element in der liste
}

static word* linkedListContains(word *list, char *entry) {
	while (list != NULL) {
		if (strcmp(list->content, entry) == 0) {
			return list;
		}
		list = list->next;
	}
	return NULL;
}

bool bucketContainsWord(word *bucket, char *entry) {
	if (linkedListContains(bucket, entry) != NULL) {
		return true;
	} else {
		return false;
	}
}

bool tableContainsWord(word **hashtable, int tablesize, char *entry) {
	unsigned int hashnumber = hash(entry, tablesize);
	return bucketContainsWord(hashtable[hashnumber], entry);
}

void printTable(word **hashtable, unsigned int tablesize) {
	printf("Start\n");
	for (int i = 0; i < tablesize; i++) {
		if (hashtable[i] == NULL) {
			printf("\tBucket[%i]\t--------------\n", i);
		} else {
			printf("\tBucket[%i]\t", i);
			printLinkedList(hashtable[i]);
			printf("\n");
		}
	}
	printf("End\n");
}

static char* stringToLower(char *word) {
	unsigned i = 0;
	char *result = calloc(1, sizeof(word) / sizeof(word[0]));
	while (word[i] != '\0') {
		result[i] = tolower(word[i]);
		i++;
	}
	return result;
}

static int compareStringLower(char *a, char *b) {
	a = stringToLower(a);
	b = stringToLower(b);
	return strcmp(a, b);
}

static word* insertIntoList(word *list, word *entry) {
	if (list->next == NULL) {
		int result = compareStringLower(entry->content, list->content);
		if (result > 0) {
			list->next = entry;
		} else {
			entry->next = list;
			list = entry;
		}
		return entry;
	} else {
		word *current = list;
		while (current->next != NULL) {
			int result = compareStringLower(entry->content, current->next->content);
			if (result < 0) {
				word *tmp = current->next;
				current->next = entry;
				entry->next = tmp;
				return entry;
			}

			current = current->next;
		}
		current->next = entry;
		return entry;

	}
	return NULL;
}

word* insertIntoTable(word **hashtable, unsigned int tablesize, char *word) {
	if(strcmp(word, "") == 0) {
		return NULL;
	}
	struct word *entry = getWordFromString(word);
	int index = hash(entry->content, tablesize);
	if (hashtable[index] == NULL) {
		hashtable[index] = entry;
		return entry;
	} else {
		struct word *tmp = linkedListContains(hashtable[index], word);
		if (tmp != NULL) {
			tmp->frequency++;
			return entry;
		} else {
			insertIntoList(hashtable[index], entry);
			return entry;
		}
	}
	return NULL;
}

word* getBucket(word **hashtable, unsigned int tablesize, unsigned int bucket) {
	if (bucket >= tablesize) {
		printf("Ungültiges Bucket");
		return NULL;
	} else {
		return hashtable[bucket];
	}
}

void printBucket(word **hashtable, unsigned int tablesize, unsigned int bucket) {
	if (bucket >= tablesize) {
		printf("Ungültiges Bucket");
	} else {
		printf("\tBucket[%u]\t", bucket);
		printLinkedList(hashtable[bucket]);
	}
}

