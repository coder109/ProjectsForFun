#include "bpe.h"

char* vocab_list[MAX_VOCAB_SIZE] = {0};
int vocab_size = 0;

bool bpe(const char* filename) {
    for(int iter_count = 0; iter_count < ITER_TIME; iter_count++) {
        if(!bpeOneIter(filename)) {
            printf("There is something wrong. Aborting...\n");
            return false;
        } else {
            if(iter_count % PRINT_TABLE_STEP_INTERVAL == 0) {
                printVocabList();
            }
            printf("Iter: %d Vocab Size: %d\n", iter_count, vocab_size);
        }
    }
    return true;
}

bool bpeOneIter(const char* filename) {
    // Read the file as bytes
    FILE* fp = fopen(filename, "rb");
    if(fp == NULL) {
        printf("Unable to read!\n");
        return false;
    }

    // Prepare the buffer
    char buffer[READ_BUFFER_SIZE] = {0};

    // Read the file until the end
    int bytes_read = 0;
    while((bytes_read = fread(buffer, 1, READ_BUFFER_SIZE, fp)) > 0) {
        
    }

    return true;
}

void printVocabList() {
    for(int i = 0; i < vocab_size; i++) {
        printf("%s\n", vocab_list[i]);
    }
}