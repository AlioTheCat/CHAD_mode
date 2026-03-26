// C++ program to illustrate the client application in the
// socket programming
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // sending connection request
    connect(clientSocket, (struct sockaddr*)&serverAddress,
            sizeof(serverAddress));

    // // sending floatvalue
    // float message = 3.5;
    // send(clientSocket, &message, sizeof(message), 0);
    
    const float container [3] = {3.5, 6.3, 7.8};

    send(clientSocket, &container, sizeof(container), 0);

    // closing socket
    close(clientSocket);

    return 0;
}