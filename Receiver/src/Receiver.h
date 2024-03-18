#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <atomic>
#include <csignal>
#include <thread>
#include <sstream>
#include <vector>

struct EncodedMessage{
    int id;
    std::string type;
    std::string encoderType;
    std::string quality;
    int value;
};

class Receiver {
    private:
        // Variables
        int id;
        bool active;
        int port;
        int receiverSocket;
        int clientSocket;

        // Methods
        int createSocket();
    public:
        // Constructor and Destructor
        Receiver(int ID, int port, bool active);
        ~Receiver();

        // Methods
        void receive();
        struct EncodedMessage decode(std::string message);
};

#endif