#!/bin/bash

g++ -Wall -c Item.cpp -o Item.o
g++ -Wall -c Queue.cpp -o Queue.o
g++ -Wall -c Stack.cpp -o Stack.o
g++ -Wall -c Event.cpp -o Event.o
g++ -Wall -c List.cpp -o List.o
g++ -Wall -c Simulator.cpp -o Simulator.o
g++ -Wall Item.o Queue.o Stack.o Event.o List.o Simulator.o FedEx.cpp -o FedEx

FedEx

