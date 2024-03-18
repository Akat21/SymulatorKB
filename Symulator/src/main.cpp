#include "Symulator.h"
#include <nlohmann/json.hpp>

#include <fstream>
#include <atomic>
#include <csignal>

//sudo apt-get install nlohmann-json3-dev
std::atomic<bool> running(true);

void signalHandler(int signum){
    running = false;
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
    std::signal(SIGINT, signalHandler);

    // Read the sensor configuration
    std::ifstream file("sensorConfig.json");
    if(!file.is_open()){
        std::cerr << "Error opening sensorConfig.json" << std::endl;
        return 1;
    }

    // Create the simulators
    std::vector<Symulator*> symulators = createSimulators(file);

    // Create the threads
    std::vector<std::thread> threads;

    // Start the simulators
    for(auto& symulator : symulators){
        threads.emplace_back([&symulator](){
            while(running.load()){
                // Transmit the message
                symulator->transmit();
            }
        });
    }

    // Join the threads
    for(auto &t : threads){
        t.join();
    }
}