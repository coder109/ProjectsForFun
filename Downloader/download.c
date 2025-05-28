#include "download.h"

#define BUFFER_SIZE 1024

#ifdef _WIN32
void win_download(const char* url, const char* filename) {
    // Try to create file
    DWORD dwTemp;
    HANDLE file = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(file == INVALID_HANDLE_VALUE) {
        printf("CreateFile function failed with error = %ld\n", GetLastError());
        return;
    }

    // Prepare for the connection
    HINTERNET internet = InternetOpenA("WinHTTP", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    HINTERNET url_handle = InternetOpenUrl(internet, url, NULL, 0, 0, 0);
    if(url_handle == NULL) {
        printf("InternetOpenUrl function failed with error = %ld\n", GetLastError());
        return;
    }

    // Prepare the buffer
    char buffer[BUFFER_SIZE] = {0};

    // Download
    DWORD dwBytesRead=1;
    while(dwBytesRead) {
        if(!InternetReadFile(url_handle, buffer, BUFFER_SIZE, &dwBytesRead)) {
            printf("InternetReadFile function failed with error = %ld\n", GetLastError());
        }
        WriteFile(file, buffer, dwBytesRead, &dwTemp, NULL);
    }

    // Finish
    CloseHandle(file);
    InternetCloseHandle(url_handle);
    InternetCloseHandle(internet);
}
#elif __linux__
void linux_download(const char *url, const char *filename) {}
#endif