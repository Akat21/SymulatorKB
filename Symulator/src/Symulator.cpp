#include "Symulator.h"
#include "Classifier.h"

// Constructors and Destructors
Symulator::Symulator(Sensor sensor){
    //Initialize the sensor
    this->sensor = sensor;
    this->randomValue = 0;
}

Symulator::~Symulator() {
    //Destructor
}

// Methods
void Symulator::simulate() {
    /*
        @ return void
        Simulate the sensor
    */

    //Generate a random value
    this->randomValue = this->randomizeValue();

    //Transmit the value
    this->transmit();
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

std::string Symulator::transmit() {
    /*
        @ return void
        Transmit the value of the sensor - print it to the console
    */

    //Classify the value
    this->sensor.quality = Classifier::classify(this->sensor.maxValue, this->sensor.minValue, this->randomValue);

    //Print the value to the console
    std::cout << "$FIX, " << this->sensor.id << ", " << this->sensor.type << ", " << this->randomValue << ", " << this->sensor.quality << std::endl;

    return "$FIX," + std::to_string(this->sensor.id) + "," + this->sensor.type + "," + std::to_string(this->randomValue) + "," + this->sensor.quality;
}