
CC=g++
CFLAGS=-c -g -std=c++11 -Wall 
LDFLAGS=-lSDL2 -lSDL2_image -lGLEW -lGL -lSOIL
SOURCES=src/maintest.cpp src/sdl_context.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=gl_out


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -g $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
