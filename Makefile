CC = gcc
CFLAGS = -g -Wall -Wextra -D_REENTRANT	

C_SOURCES = $(wildcard *.c)
#CPP_SOURCES = $(wildcard *.cpp)
C_OBJECTS = $(patsubst %.c,%.o,$(C_SOURCES))
#CPP_OBJECTS =$(patsubst %.cpp,%.o,$(CPP_SOURCES))


LDFLAGS = -L. -L/usr/lib 
LDLIBS = -lm -lSDL2 -lSDL2_ttf
INC = -I. -I/usr/include/SDL2

EXECUTABLE = main

$(EXECUTABLE) : $(C_OBJECTS)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(EXECUTABLE) $(C_OBJECTS)

$(C_OBJECTS) : %.o : %.c
	$(CC) $(INC) $(CFLAGS) -c $^ -o $@

#$(CPP_OBJECTS) : %.o : %.cpp
#	$(CXX) $(INC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *o $(EXECUTABLE)
