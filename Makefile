CXX      = /usr/sup/bin/clang++
CXXFLAGS = --std=c++11 -Wshadow -Wall -Wextra -g3

%.o: %.cpp $(shell echo *.h)
	$(CXX) $(CXXFLAGS) -c $<

# findpath: main.o Location.o
# 	$(CXX) -o $@ $^

findpath: findpath.cpp Location.cpp graph.cpp
	$(CXX) -o $@ $^


clean:
	rm -f rt findpath *.o

provide:
	provide comp15 rt README Makefile findpath.cpp graph.cpp graph.h \
	test.adat test.vdat


# Add some rules for rt website
include Makefile.publish
