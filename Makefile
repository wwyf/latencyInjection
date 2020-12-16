all: latency
latency: main.cpp
	g++ -o latency $^ -std=c++11
clean:
	rm latency