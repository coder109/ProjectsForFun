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
void linux_download(const char *url, const char *filename) {
    // Parse the url, remove http/https.
    char *parsed_url = strstr(url, "://");
    if(parsed_url != NULL) {
        parsed_url = parsed_url + 3;
    }

    // Get pure domain
    char* pure_domain = (char*)calloc(strlen(parsed_url) + 1, sizeof(char));
    for(int i = 0; i < strlen(parsed_url); i++) {
        if(parsed_url[i] == '/') {
            break;
        }
        pure_domain[i] = parsed_url[i];
    }

    char* file_name = (char*)calloc(strlen(parsed_url) + 1, sizeof(char));
    file_name = strstr(parsed_url, "/");
    if(file_name != NULL) {
        file_name = file_name + 1;
    }

    // Create Socket
    int main_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(main_socket < 0) {
        perror("Socket Creation Failed");
        return;
    }

    // Lookup the IP Address
    struct hostent *server = gethostbyname(pure_domain);
    if(server == NULL) {
        perror("IP Address Lookup Failed");
        return;
    }

    // Fill in the structure
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(80);
    memcpy(&server_address.sin_addr.s_addr, server->h_addr_list[0], server->h_length);

    // Try to connect with the server
    if(connect(main_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Connection Failed");
        return;
    } else {
        printf("Connected\n");
    }

    // Send the request
    char request[1024];
    sprintf(request, "GET /%s HTTP/1.1\r\nHost: %s:80\r\n\r\n", file_name, pure_domain);
    if(send(main_socket, request, strlen(request), 0) < 0) {
        perror("Request Failed");
        return;
    } else {
        printf("Request Sent\n");
    }

    // Prepare the buffer
    char buffer[BUFFER_SIZE] = {0};

    // Download
    int bytes_read = 0;
    FILE *fp = fopen(filename, "wb");
    printf("Downloading...\n");
    do {
        bytes_read = recv(main_socket, buffer, BUFFER_SIZE, 0);
        if(bytes_read > 0) {
            printf("Downloaded %d bytes\n", bytes_read);
            fwrite(buffer, sizeof(char), bytes_read, fp);
        } else if(bytes_read < 0) {
            perror("Download Failed");
            break;
        } else {
            break;
        }
    } while(bytes_read > 0);

    // Finish
    fclose(fp);
    close(main_socket);
}
#endif