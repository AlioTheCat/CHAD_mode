// C++ program to show the example of server application in
// socket programming
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include<arpa/inet.h>

using namespace std;

int main()
{
    // creating socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying the addressockaddr_in serverAddress;s
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.2.2", &(serverAddress.sin_addr));
    serverAddress.sin_port = htons(1106);

    // binding socket.
    bind(serverSocket, (struct sockaddr*)&serverAddress,
         sizeof(serverAddress));

    while (1) {

        // listening to the assigned socket
        listen(serverSocket, 5);

        // await (and accept) connection request
        int clientSocket
            = accept(serverSocket, nullptr, nullptr);

            // recieving data
            char buffer[12] = {};
            float part1;
            float part2;
            float part3;
            recv(clientSocket, buffer, sizeof(buffer), 0);

            memcpy(&part1, buffer, 4);
            memcpy(&part2, buffer+4, 4);
            memcpy(&part3, buffer+8, 4);
            cout << "Message from client: " << part1 << endl
                                            << part2 << endl
                                            << part3 << endl
                                            << endl;
    }

    // closing the socket.
    close(serverSocket);

    return 0;
}