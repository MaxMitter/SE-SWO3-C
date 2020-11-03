TARGET = prg
CC = gcc
CFLAGS = -Wall -Wconversion -std=c11 -Wpedantic -Werror=vla
LDFLAGS = 

%.o: %.c
	$(CC) $(CFLAGS) -c $<

all: $(TARGET)

$(TARGET): prg.o geo.o weight.o
	$(CC) -o $@ prg.o geo.o weight.o
  
prg.o: prg.c weight.h geo.h
geo.o: geo.c geo.h
weight.o: weight.c weight.h geo.h

clean:
	@rm -f *.o $(TARGET)