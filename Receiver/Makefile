all: compile link clean

compile:
	g++ -c src/Receiver.cpp src/main.cpp

link:
	g++ Receiver.o main.o -o main

clean:
	rm -f *.o