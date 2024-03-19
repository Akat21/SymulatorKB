all: compile link clean

compile:
	g++ -c src/Receiver.cpp src/Symulator.cpp src/Classifier.cpp src/main.cpp

link:
	g++ Receiver.o Symulator.o Classifier.o main.o -o main

clean:
	rm -f *.o