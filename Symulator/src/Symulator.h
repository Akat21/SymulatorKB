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
    int frequency;
    std::string quality;
    int minValue;
    int maxValue;
    int value;

    // Constructor
    Sensor() {}
    Sensor(int min, int max, int freq, std::string type) : minValue(min), maxValue(max), frequency(freq), type(type) {}
};

class Symulator {
    private:
        // Variables
        int simulatorSocket;
        int randomValue;
        Sensor sensor;

        // Methods
        int randomizeValue();
        int createSocket();

    public:
        // Constructor and Destructor
        Symulator(Sensor sensor);
        ~Symulator();

        // Methods
        void simulate();
        void transmit();
};

#endif