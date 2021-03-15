#ifdef WIN32
#include <winsock2.h>                // link to the winsock library, only for VC cl
#pragma comment(lib,"ws2_32.lib")   // Winsock Library
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"
int main(){
    int iSocket;
    struct sockaddr_in server_addr;
    char *server_message;
    int PORT = 8080;
    server_message = malloc(2000 * sizeof (char));
#ifdef WIN32
    WSADATA mywsadata; //your wsadata struct, it will be filled by WSAStartup

    if (WSAStartup(MAKEWORD(2, 2), &mywsadata) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
#endif
    // Create socket:
    iSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (iSocket < 0) {
        printf("Unable to create socket\n");
        return -1;
    }

    printf("Socket created successfully\n");

    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send connection request to server:
    if (connect(iSocket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Unable to connect\n");
        return -1;
    }
    printf("Connected with server successfully\n");

//    // Receive the server's response:
    if (recv(iSocket, server_message, sizeof(*server_message), 0) < 0) {
        printf("Error while receiving server's msg\n");
        return -1;
    }
    printf("%c\n", *server_message);

    memset(server_message, '\0', sizeof(*server_message));
    while (1) {
        int error = recv(iSocket, server_message, sizeof(Person), 0);
        if (error< 0) {
            printf("Error while receiving server's msg: %d\n", error);
            return -1;
        }
        if (strlen(server_message) > 0) {
            printf("Message  %s\n", server_message);
            Person *person;
            person = (Person*) server_message;
            printf("%s\n", person->personFirstName);
            printf("%s\n", person->personLastName);
            memset(server_message, '\0', sizeof(*server_message));
        }

    }

#ifdef WIN32
    closesocket(iSocket);
    WSACleanup();
#else
    close(iSocket);
#endif
}