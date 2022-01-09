CC=gcc
LD=gcc

CFLAGS=-Iinclude

FILES=$(wildcard src/*)

.DEFAULT_TAGET := all

%.c.o: %.c
	$(CC) -c $(CFLAGS) $? -o build/$(notdir $@)

all: $(addsuffix .o, $(FILES))
	echo FILES $(FILES)
	$(LD) $(LDFLAGS) $(wildcard build/*) -o result.exe

clean:
	rmdir build
	mkdir build