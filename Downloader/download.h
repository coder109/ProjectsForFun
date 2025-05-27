#ifndef DOWNLOAD_H_
#define DOWNLOAD_H_

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <ws2def.h>
#include <windows.h>
#elif __linux__
#include <unistd.h>
#include <netinet/in.h>
#endif

#ifdef _WIN32
void win_tcp_download(const char* url, const int port, const char* filename);
BOOL write_into_file(char* buffer, const char* filename);
#elif __linux__
void linux_download(const char* url, const char* filename);
#endif

#endif