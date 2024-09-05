.PHONY:all
all:tcpserverd tcpclient

tcpserverd:tcpserver.cpp Log.hpp tcpserverd.hpp threadpool.h dictionary.hpp
	g++ -o $@ $^ -std=c++11 -lpthread
tcpclient:tcpclient.cpp Log.hpp tcpserverd.hpp 
	g++ -o $@ $^ -std=c++11 
.PHONY:clean
clean:
	rm -f tcpclient tcpserverd