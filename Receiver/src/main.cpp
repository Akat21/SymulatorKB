#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0){
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Configure the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(55555);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
        std::cerr << "Error binding socket to server address" << std::endl;
        return 1;
    }

    // Listen for connections
    if(listen(serverSocket, 1) < 0){
        std::cerr << "Error listening for connections" << std::endl;
        return 1;
    }

    std::cout << "Server is listening for connections" << std::endl;

    // Accept a connection
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if(clientSocket < 0){
        std::cerr << "Error accepting connection" << std::endl;
        return 1;
    }

    std::cout << "Client connected" << std::endl;

    // Receive a message from the client
    std::string message;
    char buffer[1024];
    while(true){
        int bytesReceived = recv(clientSocket, buffer, 1024, 0);
        if(bytesReceived < 0){
            std::cerr << "Error receiving message from client" << std::endl;
            return 1;
        }
        if(bytesReceived == 0){
            std::cout << "Client disconnected" << std::endl;
            break;
        }
        message.append(buffer, bytesReceived);
        std::cout << "Client says: " << message << std::endl;
    }


    // Close the socket
    close(serverSocket);
    close(clientSocket);

    return 0;
}