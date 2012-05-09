g++ -Wall -shared -c Item.cpp -o Item.dll
g++ -Wall -shared -c Queue.cpp -o Queue.dll
g++ -Wall -shared -c Stack.cpp -o Stack.dll
g++ -Wall -shared -c Event.cpp -o Event.dll
g++ -Wall -shared -c List.cpp -o List.dll
g++ -Wall -shared -c Simulator.cpp -o Simulator.dll
g++ -Wall Item.dll Queue.dll Stack.dll Event.dll List.dll Simulator.dll FedEx.cpp -o FedEx.exe

FedEx.exe

Pause
