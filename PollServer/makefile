.PHONY:all
all:PollServer Client

PollServer:Main.cpp
	g++ -o $@ $^ -std=c++11
Client:Client.cpp
	g++ -o $@ $^ -std=c++11
.PHONY:clean
clean:
	rm -f PollServer