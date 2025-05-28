#ifndef BPE_H_
#define BPE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VOCAB_SIZE 10000
#define ITER_TIME 100
#define PRINT_TABLE_STEP_INTERVAL 5
#define READ_BUFFER_SIZE 1024

extern char* vocab_list[MAX_VOCAB_SIZE];
extern int vocab_size;

bool bpe(const char* filename);

bool bpeOneIter(const char* filename);

void printVocabList();

#endif