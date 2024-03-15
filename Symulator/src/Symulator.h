#ifndef SYMULATOR_H
#define SYMULATOR_H

#include<iostream>
#include <string>

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
        int randomValue;
        Sensor sensor;

    public:
        // Constructor and Destructor
        Symulator(Sensor sensor);
        ~Symulator();

        // Methods
        void simulate();
        int randomizeValue();
        std::string transmit();
};

#endif