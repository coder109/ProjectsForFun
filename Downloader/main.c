#include "download.h"

#include <stdio.h>

int main(int argc, char** argv) {
    // Args Check
    if(argc != 3) {
        printf("Current Args: %d\n", argc);
        printf("Usage: %s [URL] [FILE_PATH]\n", argv[0]);
        printf("Example: downloader.exe https://www.coderlock.site/bg.jpg bg.jpg\n");
        return 1;
    }
    // Download
    win_download(argv[1], argv[2]);

    return 0;
}