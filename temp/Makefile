#compiler
CC = g++

#compiler flags:
# -Wall	Turns on most compiler warnings
CFLAGS = -Wall

#the target executable
TARGET = test

#linker flags
LINKER = /usr/local/lib/libSDL2.dylib

#include flags
INCLUDE = -I/usr/local/include

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(LINKER) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)
