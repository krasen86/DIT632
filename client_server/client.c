#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "person.h"

int main(){
    int iSocket;
    struct sockaddr_in server_addr;
    char *server_message;
    int PORT = 8080;
    server_message = malloc(2000 * sizeof (char));

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

    // Receive the server's response:
    if (recv(iSocket, server_message, sizeof(server_message), 0) < 0) {
        printf("Error while receiving server's msg\n");
        return -1;
    }
    printf("%c\n", *server_message);

    memset(server_message, '\0', sizeof(*server_message));

        if (recv(iSocket, server_message, sizeof(char) * 20000, 0) < 0) {
            printf("Error while receiving server's msg\n");
            return -1;
        }
    printf("Message: %s\n", server_message);

    Person *person;
    person = (Person*) server_message;
    printf("%s\n", person->personFirstName);
    printf("%s\n", person->personLastName);
    memset(server_message, '\0', sizeof(*server_message));

    close(iSocket);
}