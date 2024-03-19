#include "Symulator.h"
#include "Receiver.h"
#include <nlohmann/json.hpp>

#include <fstream>

std::vector<Receiver*> createReceiver(std::ifstream& file) {
    /*
        @ return std::vector<Simulator>
        Creates the simulators
    */

    std::vector<Receiver*> receivers;
    nlohmann::json json;
    file >> json;

    for(auto& receiver : json["Receivers"]){
        receivers.push_back(new Receiver(receiver["ID"], receiver["Port"], receiver["Active"]));
    }

    return receivers;
}

std::vector<Symulator*> createSimulators(std::ifstream& file) {
    /*
        @ return std::vector<Simulator>
        Creates the simulators
    */
    std::vector<Symulator*> symulators;
    nlohmann::json json;
    file >> json;

    for(auto& sensor : json["Sensors"]){
        symulators.push_back(new Symulator(Sensor(
            sensor["ID"],
            sensor["Type"],
            sensor["MinValue"],
            sensor["MaxValue"],
            sensor["EncoderType"],
            sensor["Frequency"]
        ), sensor["Port"]));
    }

    return symulators;
}

int main(){

    // ***************************Receiver*************************** //


    
    // Read the sensor configuration for the receivers
    std::ifstream file1("receiverConfig.json");
    if(!file1.is_open()){
        std::cerr << "Error opening sensorConfig.json" << std::endl;
        return 1;
    }

    // Create the receivers
    std::vector<Receiver*> receivers = createReceiver(file1);

    // Create the threads for the receivers
    std::vector<std::thread> receiversThreads;
    
    // Start the receivers
    for(auto& receiver : receivers){
        receiversThreads.emplace_back([&receiver](){
            // Listen for messages
            receiver->receive();
        });
    }


    // ***************************Symulator*************************** //


    // Read the sensor configuration for the simulators
    std::ifstream file2("sensorConfig.json");
    if(!file2.is_open()){
        std::cerr << "Error opening sensorConfig.json" << std::endl;
        return 1;
    }

    // Create the simulators
    std::vector<Symulator*> symulators = createSimulators(file2);

    // Create the threads for the simulators
    std::vector<std::thread> symulatorsThreads;

    // Start the simulators
    for(auto& symulator : symulators){
        symulatorsThreads.emplace_back([&symulator](){
            while(true){
                // Transmit the message to the receivers
                symulator->transmit();
            }
        });
    }

    // Join the threads for the simulators
    for(auto &t : symulatorsThreads){
        t.join();
    }

    // Join the threads for the receivers
    for(auto &t : receiversThreads){
        t.join();
    }
}