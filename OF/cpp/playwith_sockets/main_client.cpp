// C++ program to illustrate the client application in the
// socket programming
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include<arpa/inet.h>

float randommm(){
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    // creating socket
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("192.168.2.2");
    serverAddress.sin_port = htons(1106);

    socklen_t len = sizeof(serverAddress);

    // // sending connection request
    // connect(clientSocket, (struct sockaddr*)&serverAddress,
    //         sizeof(serverAddress));

    // // sending floatvalue
    // float message = 3.5;
    // send(clientSocket, &message, sizeof(message), 0);
    
    float container [3] = {randommm(), randommm(), randommm()};
    std::cout << "Première valeur" << std::endl;
    std::cin >> container[0];
    container[1] = container[0];
    container[2] = container[0];

    sendto(clientSocket, &container, sizeof(container), MSG_DONTWAIT,
            (const sockaddr*) &serverAddress, len);

    // closing socket
    close(clientSocket);

    std::cout << "sent numbers " << container[0] << 
                            ", " << container[1] << 
                            ", " << container[2] << std::endl;

    return 0;
}