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
    FILE* fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Unable to read!\n");
        return false;
    }

    // Prepare the buffer
    char buffer[READ_BUFFER_SIZE] = {0};

    // Read the file until the end
    int bytes_read = 0;
    while((bytes_read = fread(buffer, 1, READ_BUFFER_SIZE, fp)) > 0) {
        bpeOneBlock(buffer);
    }

    return true;
}

bool bpeOneBlock(const char* block_string) {
    int window_begin = 0, window_end = window_begin + WINDOW_SIZE;
    if(window_end > strlen(block_string)) {
        return false;
    }

    DynamicTable* pattern_table = CreateEmptyDynamicTable(DYNAMICTABLE_DEFAULT_SIZE);
    while(true) {
        // Get the patterns and Freqs
        for(; window_end <= strlen(block_string); window_end++) {
            int freq = 1;
            // Get the pattern
            window_pattern_freq_elem* pattern_freq = (window_pattern_freq_elem*)malloc(sizeof(window_pattern_freq_elem));
            for(int i = window_begin; i < window_end; i++) {
                pattern_freq->pattern[i - window_begin] = block_string[i];
            }
            // Get the freq
            int first_occur_index = GetElementFirstIndex(pattern_table, pattern_freq);
            if(first_occur_index == -1) {
                PushIntoTable(pattern_freq, sizeof(window_pattern_freq_elem), pattern_table);
            } else {
                window_pattern_freq_elem* first_occur = (window_pattern_freq_elem*)pattern_table->table[first_occur_index].data;
                first_occur->freq += 1;
            }
        }
        // Reset the window
        window_begin = 0;
        window_end = window_begin + WINDOW_SIZE;
    }

    return true;
}

void printVocabList() {
    for(int i = 0; i < vocab_size; i++) {
        printf("%s\n", vocab_list[i]);
    }
}

void updateVocabList(char* pattern) {
    vocab_list[vocab_size] = pattern;
    vocab_size += 1;
}