#include "Symulator.h"
#include "Classifier.h"

// Constructors and Destructors
Symulator::Symulator(Sensor sensor, std::vector<int> ports){

    //Initialize symulator
    this->sensor = sensor;
    this->ports = ports;
    this->randomValue = 0;

    //Create sockets
    this->createSockets();
}

Symulator::~Symulator() {
    //Destructor
    for(auto& socket : this->simulatorSockets){
        close(socket);
    }
}

// Methods
void Symulator::createSockets() {
    /*
        @ return int
        Create a socket
    */

   for(auto& port : this->ports){
        // Create a socket
        int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if(clientSocket < 0){
            std::cerr << "Error creating socket" << std::endl;
        }
        
        // Configure the server address
        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        // Connect to the server
        if(connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
            std::cerr << "Receiver on port " << port << " inactive" << std::endl;
            continue;
        }

        this->simulatorSockets.push_back(clientSocket);
    }
}

void Symulator::simulate() {
    /*
        @ return void
        Simulate the sensor
    */

    //Generate a random value
    this->randomValue = this->randomizeValue();

    // Frequency in Hz
    double frequency = static_cast<double>(this->sensor.frequency);
    std::chrono::milliseconds sleepDuration(static_cast<int>(1000.0 / frequency));

    //Sleep for the duration
    std::this_thread::sleep_for(sleepDuration);
}

int Symulator::randomizeValue(){
    /*
        @ return int

        Set the value of the sensor to a random value between the min and max value
    */

    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Generate a random value
    int value = rand() % (this->sensor.maxValue - this->sensor.minValue + 1) + this->sensor.minValue;

    return value;
}

void Symulator::transmit() {
    /*
        @ return void
        Transmit the value of the sensor - print it to the console
    */

    std::vector<std::thread> threads;

    for(int idx = 0; idx < this->ports.size(); idx++){
        threads.emplace_back([this, idx](){
            //Simulate the sensor
            this->simulate();
            
            //Classify the value
            this->sensor.quality = Classifier::classify(this->sensor.maxValue, this->sensor.minValue, this->randomValue);

            std::string message = "$FIX," + std::to_string(this->sensor.id) + "," + this->sensor.type + "," + std::to_string(this->randomValue) + "," + this->sensor.quality;
            
            send(this->simulatorSockets[idx], message.c_str(), message.size() + 1, 0); 
        });
    }

    for(auto &t : threads){
        t.join();
    }
}