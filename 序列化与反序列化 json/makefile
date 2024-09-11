.PHONY:all
all:Servercal Clientcal

Lib=-ljsoncpp
Servercal:Protocol.hpp Servercal.hpp Socket.hpp Servercal.cpp
	g++ -o $@ $^ -std=c++11 $(Lib) 
Clientcal:Clientcal.cpp
	g++ -o $@ $^ -std=c++11 $(Lib)
.PHONY:clean
clean:
	rm Clientcal Servercal