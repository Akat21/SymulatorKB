#include "Receiver.h"

// Signal handler
std::atomic<bool> running(true);
void signalHandler(int signum){
    running = false;
}

// Constructor and Destructor
Receiver::Receiver(int ID, int port, bool active) {
    this->id = ID;
    this->port = port;
    this->active = active;
    this->receiverSocket = createSocket();
}

Receiver::~Receiver() {
    close(this->receiverSocket);
}

// Methods
int Receiver::createSocket() {
    /*
        @ return int
        Create a socket for the receiver
    */

    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0){
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Configure the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(this->port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
        std::cerr << "Error binding socket to server address" << std::endl;
        return 1;
    }
    
    return serverSocket;
}

void Receiver::receive() {
    /*
        @ return void
        Receive a message from the client
    */

    // Listen for connections
    if(listen(this->receiverSocket, 1) < 0){
        std::cerr << "Error listening for connections" << std::endl;
        exit(0);
    }

    // Accept a connection
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(this->receiverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if(clientSocket < 0){
        std::cerr << "Error accepting connection" << std::endl;
        return;
    }

    while(true){
        // Receive a message from the client
        std::string message;
        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, 1024, 0);
        if(bytesReceived < 0){
            std::cerr << "Error receiving message from client" << std::endl;
            return;
        }
        if(bytesReceived == 0){
            break;
        }

        // Process the message
        message = std::string(buffer, 0, bytesReceived);

        // Decode the message
        struct EncodedMessage encodedMessage = decode(message);

        // Print the message with color
        if (encodedMessage.quality == "Warning") {
            std::cout << "\033[33m"; 
        } else if (encodedMessage.quality == "Alarm") {
            std::cout << "\033[31m"; 
        }

        std::cout << "Receiver nr." << this->id << " - Sensor Type: " << encodedMessage.type << ", ID: " << encodedMessage.id << ", Value: " << encodedMessage.value << ", Encoding Type: " << encodedMessage.encoderType << ", Quality: " << encodedMessage.quality << std::endl;

        std::cout << "\033[0m"; // Reset font color to default
    }

    close(clientSocket);
}

struct EncodedMessage Receiver::decode(std::string message) {
    /*
        @ return struct EncodedMessage
        Decode the message
    */

    struct EncodedMessage encodedMessage;

    // Parse the message
    std::stringstream ss(message);
    std::string token;
    std::vector<std::string> tokens;
    while(std::getline(ss, token, ',')){
        tokens.push_back(token);
    }

    // Set the values
    encodedMessage.encoderType = tokens[0];
    encodedMessage.id = std::stoi(tokens[1]);
    encodedMessage.type = tokens[2];
    encodedMessage.value = std::stoi(tokens[3]);
    encodedMessage.quality = tokens[4];

    return encodedMessage;
}