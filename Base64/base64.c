#include "base64.h"

static const char* index_to_char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_encode(const unsigned char* data, unsigned int len) {
    int char_count = 0;
    char* buffer = (char*)calloc(4, sizeof(char));

    for(int i = 0; i < len; i++) {
        // Check if the buffer is full
        if(char_count == 3) {
            // Output the cipher result.
            // Original Buffer:
            // XXXXXX|XX YYYY|YYYY ZZ|ZZZZZZ

            // First Char 00XXXXXX
            printf("%c", index_to_char[data[0] >> 2]);
            
            // Second Char 00XXYYYY
            printf("%c", index_to_char[0x3f & (data[0] << 4 + data[1] >> 4)]);

            // Third Char 00YYYYZZ 
            printf("%c", index_to_char[0x3f & (data[1] << 4 + data[2] >> 6)]);

            // Fourth Char 00ZZZZZZ
            printf("%c", index_to_char[0x3f & data[2]]);

            // Reset Buffer and char_count
            char_count = 0;
            for(int j = 0; j < 3; j++) {
                buffer[j] = '\0';
            }
        }

        // Read chars into buffer
        buffer[char_count] = data[i];
        char_count++;
    }

    if(char_count == 1) {
        // Seq: XXXXXX | XX0000 | = | =
        // First Char 00XXXXXX
        printf("%c", index_to_char[data[0] >> 2]);
        // Second Char 00XX0000
        printf("%c==", index_to_char[0x3f & (data[0] << 4)]);
    } else if(char_count == 2) {
        // Seq: XXXXXX | XXYYYY | YYYY00 | =
        // First Char 00XXXXXX
        printf("%c", index_to_char[data[0] >> 2]);
        // Second Char 00XXYYYY
        printf("%c", index_to_char[0x3f & (data[0] << 4 | data[1] >> 4)]);
        // Third Char 00YYYY00
        printf("%c=", index_to_char[0x3f & (data[1] << 4)]);
    }
}