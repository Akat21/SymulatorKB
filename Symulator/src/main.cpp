#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <thread>
#include <chrono>

#include "Symulator.h"

int main(){
    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0){
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Configure the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(55555);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if(connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
        std::cerr << "Error connecting to server" << std::endl;
        return 1;
    }

    // Send a messages to the server
    Symulator symulator(Sensor(0, 100, 1, "Temperature"));
    Symulator symulator2(Sensor(-10, 100, 2, "Pressure"));
    Symulator symulator3(Sensor(-10, 10000, 4, "Humidity"));

    while(true){
        symulator.simulate();
        send(clientSocket, symulator.transmit().c_str(), symulator.transmit().size() + 1, 0);
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // symulator2.simulate();
        // send(clientSocket, symulator2.transmit().c_str(), symulator2.transmit().size() + 1, 0);
        // std::this_thread::sleep_for(std::chrono::seconds(2));

        // symulator3.simulate();
        // send(clientSocket, symulator3.transmit().c_str(), symulator3.transmit().size() + 1, 0);
        // std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "Connected to server" << std::endl;

    // Close the socket
    close(clientSocket);
}