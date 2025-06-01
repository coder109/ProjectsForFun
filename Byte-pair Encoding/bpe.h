#ifndef BPE_H_
#define BPE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "DynamicTable.h"

#define MAX_VOCAB_SIZE 10000
#define ITER_TIME 100
#define PRINT_TABLE_STEP_INTERVAL 5
#define READ_BUFFER_SIZE 1024
#define WINDOW_SIZE 2
#define STACK_SIZE 1024

extern char* vocab_list[MAX_VOCAB_SIZE];
extern int vocab_size;

typedef struct {
    char* pattern[WINDOW_SIZE];
    int freq;
} window_pattern_freq_elem;

bool bpe(const char* filename);

bool bpeOneIter(const char* filename);

bool bpeOneBlock(const char* block_string);

void printVocabList();

int getMaxFreqInStack();

void updateVocabList(char* pattern);

#endif