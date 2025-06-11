#ifndef BASE64_H
#define BASE64_H

#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

void base64_encode(const unsigned char* data, unsigned int len);

void base64_decode(const char* data, unsigned int len);

#endif