# Compilateur
CCPP:=g++

# Sources & objets
SRC= $(wildcard *.cpp) $(wildcard ../lib/cbor/*.cpp) $(wildcard ../lib/tinyxml2/*.cpp)
OBJ= $(SRC:.cpp=.o)

# options de compilation
CPPFLAGS := -std=c++11 -Wall -Wextra -pedantic -ggdb

# executable
EXEC = serveur

CXXFLAGS = $(shell pkg-config --cflags cairo gtk+-3.0 librsvg-2.0)
LDFLAGS = $(shell pkg-config --libs cairo gtk+-3.0 librsvg-2.0)

# Règle de compilation
all : clean $(EXEC)

mem : $(EXEC)
	valgrind --leak-check=full ./$<

$(EXEC) : $(OBJ)
	$(CCPP) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o : %.cpp
	$(CCPP) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

.PHONY : clean

clean :
	rm -f *.o serveur