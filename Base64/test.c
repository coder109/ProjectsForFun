#include "base64.h"

#include <string.h>

int main(int argc, char **argv) {
    char* test_seq = "This is a test sequence.";
    char* test_seq_1 = "This is a test sequence.A";
    char* test_seq_2 = "This is a test sequence.AB";
    base64_encode(test_seq, strlen(test_seq));
    base64_encode(test_seq_1, strlen(test_seq_1));
    base64_encode(test_seq_2, strlen(test_seq_2));

    char* test_seq_4 = "VGhpcyBpcyBhIHRlc3Qgc2VxdWVuY2Uu";
    char* test_seq_5 = "VGhpcyBpcyBhIHRlc3Qgc2VxdWVuY2UuQQ==";
    char* test_seq_6 = "VGhpcyBpcyBhIHRlc3Qgc2VxdWVuY2UuQUI=";
    base64_decode(test_seq_4, strlen(test_seq_4));
    base64_decode(test_seq_5, strlen(test_seq_5));
    base64_decode(test_seq_6, strlen(test_seq_6));
    return 0;
}