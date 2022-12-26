#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct word {
	char *name;
	unsigned int frequency;
	struct word *next;
} word;

static unsigned int hash(char *name, unsigned int tablesize) {
	int length = strlen(name);
	unsigned int hashvalue = 0;
	for (int i = 0; i < length; i++) {
		hashvalue += name[i];
	}
	hashvalue %= tablesize;
	return hashvalue;
}

static word* getWordFromString(char *word) {
	struct word *pointer = calloc(1, sizeof(word));
	pointer->name = word;
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
	while (list != NULL) {
		if (list->frequency >= 2)
			printf("%s(%u) - ", list->name, list->frequency);
		else
			printf("%s - ", list->name);
		list = list->next;
	}
}

static word* linkedListContains(word *list, char *entry) {
	while (list != NULL) {
		if (strcmp(list->name, entry) == 0) {
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
		int result = compareStringLower(entry->name, list->name);
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
			int result = compareStringLower(entry->name, current->next->name);
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
	struct word *entry = getWordFromString(word);
	int index = hash(entry->name, tablesize);
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
		printf("Bucket[%u]\t ", bucket);
		printLinkedList(hashtable[bucket]);
	}
}

int main(void) {
	unsigned int tablesize = 12;
	word **hashtable = calloc(1, sizeof(word) * tablesize);

	freeTable(hashtable, tablesize);
	insertIntoTable(hashtable, tablesize, "hallo");
	insertIntoTable(hashtable, tablesize, "ich");
	insertIntoTable(hashtable, tablesize, "heiße");
	insertIntoTable(hashtable, tablesize, "marwan");
	insertIntoTable(hashtable, tablesize, "schön");
	insertIntoTable(hashtable, tablesize, "Sie");
	insertIntoTable(hashtable, tablesize, "kennen");
	insertIntoTable(hashtable, tablesize, "zu");
	insertIntoTable(hashtable, tablesize, "leren");
	insertIntoTable(hashtable, tablesize, "wie");
	insertIntoTable(hashtable, tablesize, "heißen");
	insertIntoTable(hashtable, tablesize, "hallo");
	insertIntoTable(hashtable, tablesize, "sie");
	insertIntoTable(hashtable, tablesize, "wenn");
	insertIntoTable(hashtable, tablesize, "ich");
	insertIntoTable(hashtable, tablesize, "marwan");

	printTable(hashtable, tablesize);

	printBucket(hashtable, tablesize, 1);

	return 0;

}

