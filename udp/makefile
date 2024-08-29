.PHONY:all
all:server client

server:server.cpp Log.hpp udpserver.hpp
	g++ -o $@ $^ -std=c++11 
client:client.cpp Log.hpp udpserver.hpp
	g++ -o $@ $^ -std=c++11 
.PHONY:clean
clean:
	rm -f client server