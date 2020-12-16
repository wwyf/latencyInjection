all: latency
latency: main.cpp
	g++ -o latency $^ -std=c++11 -O3
clean:
	rm latency
