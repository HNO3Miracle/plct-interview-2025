# Makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

TARGETS = mixplus cnt check

all: $(TARGETS)

mixplus: mixplus.cpp
	$(CXX) $(CXXFLAGS) -o mixplus mixplus.cpp

cnt: cnt.cpp
	$(CXX) $(CXXFLAGS) -o cnt cnt.cpp

check: check.cpp
	$(CXX) $(CXXFLAGS) -o check check.cpp

clean:
	rm -f $(TARGETS)

test: all
	bash test_suite.sh