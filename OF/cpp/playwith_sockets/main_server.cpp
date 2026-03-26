// C++ program to show the example of server application in
// socket programming
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main()
{
    // creating socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying the addressockaddr_in serverAddress;s
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

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
            char* part1 = &buffer[0];
            char* part2 = &buffer[4];
            char* part3 = &buffer[8];
            recv(clientSocket, buffer, sizeof(buffer), 0);
            cout << "Message from client: " << *reinterpret_cast<const float *>(part1) << endl
                                            << *reinterpret_cast<const float *>(part2) << endl
                                            << *reinterpret_cast<const float *>(part3) << endl
                                            << endl;
    }

    // closing the socket.
    close(serverSocket);

    return 0;
}