/*
 * filereader.h
 *
 *  Created on: Jan 4, 2023
 *      Author: osboxes
 */

#ifndef FILEREADER_H_
#define FILEREADER_H_
#include "hashtable.h"

void storeFileIntoTable(char *filename, word **hashtable, unsigned int tablesize);


void copyFileWithoutBuckets(char *oldFilename, char *newFilename, word **hashtable, unsigned int tablesize, int *buckets, int bucketsize);


void copyFileWithBuckets(char *oldFilename, char *newFilename, word **hashtable, unsigned int tablesize, int *buckets, int bucketsize);




#endif /* FILEREADER_H_ */
