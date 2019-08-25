CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread -lm

all: acm_intro hailstone flipper windows

acm_intro: acm_intro.o
	$(LD) acm_intro.o $(LDFLAGS) -o acm_intro

hailstone: hailstone.o
	$(LD) hailstone.o $(LDFLAGS) -o hailstone

flipper: flipper.o
	$(LD) flipper.o $(LDFLAGS) -o flipper

windows: windows.o
	$(LD) windows.o $(LDFLAGS) -o windows

acm_intro.o : acm_intro.cpp
	$(CXX) $(CXXFLAGS) acm_intro.cpp

hailstone.o : hailstone.cpp
	$(CXX) $(CXXFLAGS) hailstone.cpp

flipper.o : flipper.cpp
	$(CXX) $(CXXFLAGS) flipper.cpp

windows.o : windows.cpp
	$(CXX) $(CXXFLAGS) windows.cpp

clean :
	-rm -f *.o $(EXENAME) test
