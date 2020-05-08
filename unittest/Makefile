SRCLIST=ArrayTest.cpp VectorTest.cpp # PixelTest.cpp
OBJLIST=$(SRCLIST:.cpp=.o)
BINLIST=$(SRCLIST:.cpp=.out)

all: $(BINLIST)

CXX := g++
CC := gcc
OPT := -O3
CFLAGS := "-I../include/"
LDFLAGS := -lGL -lGLU -lm -lGLEW -lglfw -lglut -lpng -ljpeg -lgtest -lpthread

%.o: %.c
	$(CC) $(OPT) $< -o $@ -c $(CFLAGS)

%.o: %.cpp
	$(CXX) $(OPT) $< -o $@ -c $(CFLAGS)

%.o: %.cc
	$(CXX) $(OPT) $< -o $@ -c $(CFLAGS)

%.out: %.o
	$(CXX) $(OPT) $< -o $@ $(CFLAGS) $(LDFLAGS)

check: $(BINLIST)
	for test in $(BINLIST); do ./$$test; done

clean:
	rm -f $(BINLIST) $(OBJLITS)
