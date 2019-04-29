TARGET = libsockets.so
LIBS = -lcommons
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET) install
all: clean default 

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) -shared $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

install:
	cp -u libsockets.so /usr/lib
	mkdir /usr/include/sockets
	cp --parents -u $(HEADERS) /usr/include/sockets

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -rf /usr/include/sockets/
	-rm -f *.log
