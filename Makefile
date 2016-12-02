all: scheduler

%: %.cpp
	g++ -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

