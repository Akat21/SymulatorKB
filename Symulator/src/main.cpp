#include "Symulator.h"

#include <atomic>
#include <csignal>

std::atomic<bool> running(true);

void signalHandler(int signum){
    running = false;
}

int main(){
    std::signal(SIGINT, signalHandler);

    std::vector<Symulator*> symulators = {
        new Symulator(Sensor(-10, 100, 5, "Speed")),
        new Symulator(Sensor(-10000, 10000, 1, "Position")),
        new Symulator(Sensor(0, 255, 10, "Depth"))
    };

    std::vector<std::thread> threads;

    for(auto& symulator : symulators){
        threads.emplace_back([&symulator](){
            while(running.load()){
                // Simulate the sensor
                symulator->simulate();
                
                // Transmit the message
                symulator->transmit();
            }
        });
    }

    for(auto &t : threads){
        t.join();
    }
}