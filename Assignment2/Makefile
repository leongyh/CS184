CC = g++

SRCDIR = src
BINDIR = bin

CFLAGS = -g -Ilib/glm

SOURCES = $(shell find $(SRCDIR) -type f \( -iname '*.cpp' \))
_OBJS = $(patsubst %.cpp, %.o, $(SOURCES))
OBJS = $(patsubst $(SRCDIR)/%, $(BINDIR)/%, $(_OBJS))
RM = /bin/rm -f 

all: main 

main: $(OBJS) $(BINDIR)/main.o 
	$(CC) $(CFLAGS) $^ -o as2

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BINDIR)/*
	rm -f as2