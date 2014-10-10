CC = g++

SRCDIR = src
BINDIR = bin

ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -Ilib/glut-3.7.6-bin -Ilib/glm -Ilib/lodepng
	LDFLAGS = -lGL -lglut -lGLU
endif

SOURCES = $(shell find $(SRCDIR) -type f \( -iname '*.cpp' \))
_OBJS = $(patsubst %.cpp, %.o, $(SOURCES))
OBJS = $(patsubst $(SRCDIR)/%, $(BINDIR)/%, $(_OBJS))
RM = /bin/rm -f 

all: main 

main: $(OBJS) $(BINDIR)/main.o 
	$(CC) $(CFLAGS) $^ -o as2 $(LDFLAGS) 

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BINDIR)/*
	rm -f as2