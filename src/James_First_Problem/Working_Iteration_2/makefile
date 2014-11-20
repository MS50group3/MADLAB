CFLAGS = `sdl2-config --cflags` -O4 -Wall -pedantic -std=c99 -lm
INCS = Interaction_Functions.h 
TARGET = First_Problem
SOURCES =  Interaction_Functions.c $(TARGET).c
LIBS =  `sdl2-config --libs` -lSDL2 -lSDL2_ttf
CC = gcc


all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET) 