#include "hashtable.h"

static char* removeSpaceFromString(char *string) {
	char *result = calloc(1, sizeof(string));
	unsigned int index = 0;
	while (string[index] != '\0') {
		result[index] = string[index];
		index++;
	}
	return result;
}

static bool isSpecialChar(char c) {
	char *chars = ".;:,?";
	if (strchr(chars, c) != NULL) {
		return true;
	}
	return false;
}

bool numberContainsArray(int number, int *array, int arraysize) {
	for (int i = 0; i < arraysize; i++) {
		if (number == array[i]) {
			return true;
		}
	}
	return false;
}

void storeFileIntoTable(char *filename, word **hashtable,
		unsigned int tablesize) {
	FILE *file = fopen(filename, "r");
	char c;
	if (file == NULL) {
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	char *word = calloc(1, 30);
	while ((c = fgetc(file)) != EOF) {
		if (!isspace(c) && c != '\n' && c != '\t' && isSpecialChar(c) == false) {
			strncat(word, &c, 1);
		} else {
			insertIntoTable(hashtable, tablesize, removeSpaceFromString(word));
			strcpy(word, "");
		}
	}
	free(word);
	fclose(file);
}

void copyFileWithoutBuckets(char *oldFilename, char *newFilename,
		word **hashtable, unsigned int tablesize, int *buckets, int bucketsize) {

	FILE *oldFile = fopen(oldFilename, "r");
	FILE *newFile = fopen(newFilename, "w");
	//word *allBuckets = calloc(1, sizeof(word));

	char c;
	oldFile = fopen(oldFilename, "r");
	newFile = fopen(newFilename, "w");
	char *word = calloc(1, 30);

	while ((c = fgetc(oldFile)) != EOF) {
		if (!isspace(c) && c != '\n' && c != '\t' && isSpecialChar(c) == false) {
			strncat(word, &c, 1);
		} else {

			if (tableContainsWord(hashtable, tablesize,
					word) && numberContainsArray(hash(word, tablesize), buckets, bucketsize)==false) {
				fprintf(newFile, "%s", word);
			}

			fputc(c, newFile);
			strcpy(word, "");
		}
	}

	free(word);
	fclose(oldFile);
	fclose(newFile);
}

void copyFileWithBuckets(char *oldFilename, char *newFilename, word **hashtable,
		unsigned int tablesize, int *buckets, int bucketsize) {
	FILE *oldFile = fopen(oldFilename, "r");
	FILE *newFile = fopen(newFilename, "w");
	//word *allBuckets = calloc(1, sizeof(word));

	char c;
	oldFile = fopen(oldFilename, "r");
	newFile = fopen(newFilename, "w");
	char *word = calloc(1, 30);

	while ((c = fgetc(oldFile)) != EOF) {
		if (!isspace(c) && c != '\n' && c != '\t' && isSpecialChar(c) == false) {
			strncat(word, &c, 1);
		} else {

			if (tableContainsWord(hashtable, tablesize, word)
					&& numberContainsArray(hash(word, tablesize), buckets,
							bucketsize)) {
				fprintf(newFile, "%s", word);
			}
			fputc(c, newFile);
			strcpy(word, "");
		}
	}

	fclose(oldFile);
	fclose(newFile);
}

