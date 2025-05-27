#include "download.h"

#include <stdio.h>

#define BUFFER_SIZE 1024

#ifdef _WIN32
void win_tcp_download(const char *url, const int port, const char *filename) {
    // Try to create the file
    HANDLE file = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) {
        printf("CreateFile function failed with error = %ld\n", GetLastError());
        return;
    }

    // Initialize Winsock Lib
    WSADATA wsadata = {0};
    int WSAresult = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (WSAresult != 0) {
        printf("WSAStartup function failed with error = %d\n", WSAGetLastError());
        return;
    }
    else
        printf("WSAStartup function success\n");

    // Initialize the socket.
    SOCKET main_socket = INVALID_SOCKET;
    int socket_family = AF_INET;
    int socket_type = SOCK_STREAM;
    int protocol = IPPROTO_TCP;
    main_socket = socket(socket_family, socket_type, protocol);
    if (main_socket == INVALID_SOCKET) {
        printf("socket function failed with error = %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }
    else
        printf("socket function success\n");

    // Connect to the server
    struct sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(url);
    clientService.sin_port = htons(port);

    // Prepare the buffer
    char recv_buffer[BUFFER_SIZE] = {0};

    // Connect to the server
    WSAresult = connect(main_socket, (SOCKADDR *)& clientService, sizeof(clientService));
    if (WSAresult == SOCKET_ERROR) {
        printf("connect function failed with error: %d\n", WSAGetLastError());
        WSAresult = closesocket(main_socket);
        if (WSAresult == SOCKET_ERROR)
            printf("closesocket function failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    // Send
    WSAresult = send(main_socket, recv_buffer, (int)strlen(recv_buffer), 0);
    if (WSAresult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(main_socket);
        WSACleanup();
        return;
    }

    // Shutdown the sending socket in order to receive
    WSAresult = shutdown(main_socket, SD_SEND);
    if (WSAresult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(main_socket);
        WSACleanup();
        return;
    }

    // Receive
    do {
        WSAresult = recv(main_socket, recv_buffer, (int)strlen(recv_buffer), 0);
        if (WSAresult > 0) {
            printf("Bytes received: %d\n", WSAresult);
            win_write_into_file(recv_buffer, filename);
        }
        else if (WSAresult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while(WSAresult > 0);

    // Finalize the socket
    WSACleanup();   
}

BOOL win_write_into_file(char *buffer, const char *filename) {
    // Initialize the data
    HANDLE file = CreateFile(filename, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD bytes_to_write = (DWORD)strlen(buffer);
    DWORD bytes_written = 0;

    // Check if the file was created
    if(file == INVALID_HANDLE_VALUE) {
        printf("CreateFile function failed with error = %ld\n", GetLastError());
        return FALSE;
    }

    // Try to write into the file
    BOOL write_file_flag = WriteFile(file, buffer, strlen(buffer), &bytes_written, NULL);
    if(!write_file_flag) {
        printf("WriteFile function failed with error = %ld\n", GetLastError());
        CloseHandle(file);
        return FALSE;
    } else {
        if(bytes_written != bytes_to_write) {
            printf("WriteFile function failed with error = %ld\n", GetLastError());
            CloseHandle(file);
            return FALSE;
        }
    }
    CloseHandle(file);
    return TRUE;
}
#elif __linux__
void linux_download(const char *url, const char *filename) {}
#endif