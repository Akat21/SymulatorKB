#ifndef SYMULATOR_H
#define SYMULATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <thread>
#include <chrono>

struct Sensor{
    int id;
    std::string type;
    std::string encoderType;
    int frequency;
    std::string quality;
    int minValue;
    int maxValue;
    int value;

    // Constructor
    Sensor() {}
    Sensor(int id, std::string type, int min, int max, std::string eT, int freq) :
           id(id), type(type), minValue(min), maxValue(max), encoderType(eT), frequency(freq) {}
};

class Symulator {
    private:
        // Variables
        std::vector<int> ports;
        std::vector<int> simulatorSockets;
        int randomValue;
        Sensor sensor;

        // Methods
        int randomizeValue();
        void createSockets();

    public:
        // Constructor and Destructor
        Symulator(Sensor sensor, std::vector<int> ports);
        ~Symulator();

        // Methods
        void simulate();
        void transmit();
};

#endif