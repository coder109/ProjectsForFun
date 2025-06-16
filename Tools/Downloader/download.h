#ifndef DOWNLOAD_H_
#define DOWNLOAD_H_

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#include <wininet.h>
#elif __linux__
// HTTP Support
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
// HTTPs Support
#include <openssl/ssl.h>
#include <openssl/err.h>
#endif

#ifdef _WIN32
void win_download(const char* url, const char* filename);
#elif __linux__
void linux_download(const char* url, const char* filename);
void linux_http_download(const char* url, const char* filename);
void linux_https_download(const char* url, const char* filename);
#endif

#endif