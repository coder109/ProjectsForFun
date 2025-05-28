#ifndef DOWNLOAD_H_
#define DOWNLOAD_H_

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#include <wininet.h>
#elif __linux__
#include <unistd.h>
#include <netinet/in.h>
#endif

#ifdef _WIN32
void win_download(const char* url, const char* filename);
#elif __linux__
void linux_download(const char* url, const char* filename);
#endif

#endif