#include "Receiver.h"
#include "json.hpp"

#include <vector>
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

int main(){
    // Read the sensor configuration
    std::ifstream file("receiverConfig.json");
    if(!file.is_open()){
        std::cerr << "Error opening sensorConfig.json" << std::endl;
        return 1;
    }

    // Create the receivers
    std::vector<Receiver*> receivers = createReceiver(file);

    // Create the threads
    std::vector<std::thread> threads;
    
    // Start the receivers
    for(auto& receiver : receivers){
        threads.emplace_back([&receiver](){
            // Receive the message
            receiver->receive();
        });
    }

    // Join the threads
    for(auto &t : threads){
        t.join();
    }

    return 0;
}