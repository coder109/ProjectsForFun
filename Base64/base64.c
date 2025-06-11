#include "base64.h"

static const char* index_to_char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int char_to_index(char c) {
    for(int i = 0; i < 64; i++) {
        if(index_to_char[i] == c) {
            return i;
        }
    }
    return -1;
}

void base64_encode(const char* data, unsigned int len) {
    int char_count = 0;
    char* buffer = (char*)calloc(3, sizeof(char));

    for(int i = 0; i < len; i++) {
        // Read chars into buffer
        buffer[char_count] = data[i];
        char_count++;

        // Check if the buffer is full
        if(char_count == 3) {
            // Output the cipher result.
            // Original Buffer:
            // XXXXXX|XX YYYY|YYYY ZZ|ZZZZZZ
            // First Char 00XXXXXX
            printf("%c", index_to_char[buffer[0] >> 2]);
            
            // Second Char 00XXYYYY
            printf("%c", index_to_char[0x3f & (buffer[0] << 4 | buffer[1] >> 4)]);

            // Third Char 00YYYYZZ 
            printf("%c", index_to_char[0x3f & (buffer[1] << 2 | buffer[2] >> 6)]);

            // Fourth Char 00ZZZZZZ
            printf("%c", index_to_char[0x3f & buffer[2]]);

            // Reset Buffer and char_count
            char_count = 0;
        }
    }

    if(char_count == 1) {
        // Seq: XXXXXX | XX0000 | = | =
        // First Char 00XXXXXX
        printf("%c", index_to_char[buffer[0] >> 2]);
        // Second Char 00XX0000
        printf("%c==", index_to_char[0x30 & (buffer[0] << 4)]);
    } else if(char_count == 2) {
        // Seq: XXXXXX | XXYYYY | YYYY00 | =
        // First Char 00XXXXXX
        printf("%c", index_to_char[buffer[0] >> 2]);
        // Second Char 00XXYYYY
        printf("%c", index_to_char[0x3f & (buffer[0] << 4 | buffer[1] >> 4)]);
        // Third Char 00YYYY00
        printf("%c=", index_to_char[0x3f & (buffer[1] << 2)]);
    }
    printf("\n");
}

void base64_decode(const char* data, unsigned int len) {
    int char_count = 0;
    int* buffer = (int*)calloc(4, sizeof(int));

    int pad_id = char_to_index('=');
    
    for(int i = 0; i < len; i++) {
        // Read chars into buffer
        buffer[char_count] = char_to_index(data[i]);
        if(buffer[char_count] == -1 && data[i] != '=') {
            printf("Invalid Char: %c\n", data[i]);
            return;
        }
        char_count++;

        // Parse If 4
        if(char_count == 4 && buffer[3] != pad_id) {
            // Output the cipher result.
            // Original Buffer: 00XXXXXX 00XXYYYY 00YYYYZZ 00ZZZZZZ
            // First Char: XXXXXXXX
            printf("%c", buffer[0] << 2 | buffer[1] >> 4);
            // Second Char: YYYYYYYY
            printf("%c", buffer[1] << 4 | buffer[2] >> 2);
            // Third Char: ZZZZZZZZ
            printf("%c", buffer[2] << 6 | buffer[3]);
        } else if(char_count == 4 && buffer[3] == pad_id && buffer[2] != pad_id) {
            // Original Buffer: 00XXXXXX 00XXYYYY 00YYYY00 =
            // First Char: XXXXXXXX
            printf("%c", buffer[0] << 2 | buffer[1] >> 4);
            // Second Char: YYYYYYYY
            printf("%c", buffer[1] << 4 | buffer[2] >> 2);
        } else if(char_count == 4 && buffer[3] == pad_id && buffer[2] == pad_id) {
            // Original Buffer: 00XXXXXX 00XX0000 = =
            // First Char: XXXXXXXX
            printf("%c", buffer[0] << 2 | buffer[1] >> 4);
        }

        if(char_count == 4) {
            // Reset
            char_count = 0;
        }
    }
    printf("\n");
}