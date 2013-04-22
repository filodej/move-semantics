TARGET = convert
LIBS = -lstdc++ -lm -ldl
#-lmudflap
CC = gcc
CFLAGS = -O0 -g3 -ggdb3 -Wall -Wextra -Werror -ansi -pedantic -pedantic-errors -std=c++0x
#-fmudflap -fbounds-check
#
HEADERS = convert.hpp convert_impl.hpp conversions.hpp
OBJECTS = main.o

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