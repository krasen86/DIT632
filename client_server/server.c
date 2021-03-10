#ifdef WIN32
#include <winsock2.h>                // link to the winsock library, only for VC cl
#pragma comment(lib,"ws2_32.lib")   // Winsock Library
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#endif
#include "person.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

void populateList();

int main(){
    populateList();
    printList();
#ifdef WIN32
    WSADATA wsa;
#endif
    int server_fd;      // server file description
    int iSocket;        // socket id
    struct sockaddr_in addrSocket;  // socket's address
    int opt = 1;         // broadcast, which is a standard protocol for IPv4
    int PORT = 8080;

    int iAddrLen = sizeof(addrSocket);

    char* strReply = malloc(sizeof (char));
    sprintf(strReply, "%d", getNumberOfPersons());
#ifdef WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
#endif
    // Creating socket file descriptor
    // IPv4 and TCP
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        printf("Error: Could not create socket: %s. Exiting...\n", strerror(errno));
        exit(1);
    }

    // Attaching the socket to our address
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        printf("Error: Could not attach: %s. Exiting...\n", strerror(errno));
        exit(1);
    }

    // specifying the protocols and addresses from which we accept the connections
    addrSocket.sin_family = AF_INET;            // protocol
    addrSocket.sin_addr.s_addr = INADDR_ANY;    // address
    addrSocket.sin_port = htons(PORT);          // port

    // attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *) &addrSocket, iAddrLen) < 0) {
        printf("Error: Could not bind: %s. Exiting...\n", strerror(errno));
        exit(1);
    }
    // now we just wait and listen for the connections from clients
    // the second parameter is the number of connections to be put in queue before rejecting them
    // here, we put 1
    if (listen(server_fd, 1) < 0) {
        printf("Error: Could not listen: %s. Exiting...\n", strerror(errno));
        exit(1);
    }

    // once we get a connect, we accept it
    iSocket = accept(server_fd, (struct sockaddr *) &addrSocket, (int *) &iAddrLen);

    // for fail-safe program, we check if the socket is actually created and the connection is accepted
    if (iSocket < 0) {
        printf("Error: Could not accept a connection: %s. Exiting...\n", strerror(errno));
        exit(1);
    }
//    // send something over the socket
    if (send(iSocket, strReply, 1, 0) < 0) {
        printf("Error sending the message to the client %s. Not really a problem on our side. \n", strerror(errno));
    }
    List *temp = head;
    while (temp) {
        Person *person = &temp->person;
        if (send(iSocket, person, sizeof (*person), 0) < 0) {
            printf("Error sending the message to the client %s. Not really a problem on our side. \n", strerror(errno));
        }
        temp = temp -> next;
    }
    // Close the socket
#ifdef WIN32
    closesocket(iSocket);
    WSACleanup();
#else
    close(iSocket);
#endif


}

void printList(){
    List *temp = head;
    int i = 0;
    if(temp == NULL){
        printf("List is empty");
    }else {
        while (temp != NULL) {
            i++;
            printf("%d: %s ", i, temp -> person.personFirstName);
            printf("%s\n", temp -> person.personLastName);
            temp = temp -> next;
        }
    }
}

void populateList(){
    Person person;
    strcpy(person.personFirstName, "Krasen");
    strcpy(person.personLastName, "Parvanov");
    insertPerson(person);
    Person person2;
    strcpy(person2.personFirstName, "Chrysostomos");
    strcpy(person2.personLastName, "Tsagkidis");
    insertPerson(person2);
    Person person3;
    strcpy(person3.personFirstName, "Eemil");
    strcpy(person3.personLastName, "Jeskanen");
    insertPerson(person3);
    Person person4;
    strcpy(person4.personFirstName, "Donald");
    strcpy(person4.personLastName, "Trump");
    insertPerson(person4);
    Person person5;
    strcpy(person5.personFirstName, "Barack");
    strcpy(person5.personLastName, "Obama");
    insertPerson(person5);

}