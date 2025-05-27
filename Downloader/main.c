#include "download.h"

#include <stdio.h>

int main(int argc, char** argv) {
    // Args Check
    if(argc != 4) {
        printf("Current Args: %d\n", argc);
        printf("Usage: %s [URL] [PORT] [FILE_PATH]\n", argv[0]);
        printf("Example: downloader.exe https://www.coderlock.site/bg.jpg bg.jpg\n");
        return 1;
    }
    // Download
    win_tcp_download(argv[1], (int)atoi(argv[2]), argv[3]);

    return 0;
}