#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include<string>

class Classifier{
    public:
        static std::string classify(int maxValue, int minValue, int value);
};

#endif