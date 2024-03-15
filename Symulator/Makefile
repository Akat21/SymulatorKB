all: compile link clean

compile:
	g++ -c src/Symulator.cpp src/Classifier.cpp src/main.cpp

link:
	g++ Symulator.o Classifier.o main.o -o main

clean:
	rm -f *.o