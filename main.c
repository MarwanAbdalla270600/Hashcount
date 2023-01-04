#include "filereader.h"

int main(void) {

	unsigned int tablesize = 7;
	word **hashtable = calloc(1, sizeof(word) * tablesize);

	storeFileIntoTable("testfile.txt", hashtable, tablesize);

	printTable(hashtable, tablesize);

//	printf("%i\n", tableContainsWord(hashtable, tablesize, "change"));


	int buckets[1] = {6};


	//printBucket(hashtable, tablesize, 1);
	//freeTable(hashtable, tablesize);



	copyFileWithBuckets("testfile.txt", "newfile.txt", hashtable, tablesize, buckets, 1);
	//copyFileWithoutBuckets("newfile.txt", "newfile.txt", hashtable, tablesize, 2);

	//copyFileWithBuckets("testfile.txt", "newfile.txt", hashtable, tablesize, 3);

	freeTable(hashtable, tablesize);
	return 0;

}
