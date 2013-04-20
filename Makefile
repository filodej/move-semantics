TARGET = movement
LIBS = -lstdc++ -lm -ldl 
#-lmudflap
CC = gcc
CFLAGS = -O0 -g3 -ggdb3 -fbounds-check -Wall -Wextra -Werror -ansi -pedantic -pedantic-errors -std=c++11
#-fmudflap 
#
HEADERS = movement.cpp
OBJECTS = movement.o

default: $(TARGET)
all: default

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)