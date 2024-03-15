#include "Classifier.h"

std::string Classifier::classify(int maxValue, int minValue, int value) {
    /*
        @ return std::string
        
        Classify the value of the sensor as "Alarm", "Warning" or "Normal"
    */

    int range = maxValue - minValue; //Length of the range of values
    std::string quality;

    //Classify the value - based on the percentage of the range
    if(value < minValue + range * 0.10 || value > maxValue - range * 0.10) {
        quality = "Alarm";
    } else if(value < minValue + range * 0.20 || value > maxValue - range * 0.20) {
        quality = "Warning";
    } else {
        quality = "Normal";
    }

    return quality;
}