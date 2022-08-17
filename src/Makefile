CXX=g++
CC=$(CXX)
CFLAGS = -std=c++11 -Ofast
CXXFLAGS=$(CFLAGS)
OBJS = main.o
all: main
	mv main fc
main: $(OBJS)

clean:
	rm -f $(OBJS)  fc
redo: clean all
