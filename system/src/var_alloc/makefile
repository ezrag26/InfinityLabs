# C compiler
CC = gcc

#compiler flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
CRELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

#includes
INCLUDES = -I../../../include

#libraries from -L../lib
LFLAGS = -L../../lib

#use libraries, like -lm
LIBS =

#destinations
DEST:=../../obj
EXEF = ../../test

#c sources
SRCS:= $(wildcard *.c)

#obj files
OBJS:= $(addprefix $(DEST)/, $(patsubst %.c, %.o, $(SRCS)))

#exe name
MAIN = $(addprefix $(EXEF)/, $(notdir $(CURDIR)))

# generic from here forward

$(DEST)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

all: $(OBJS)

run: $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $^

test: $(MAIN)
	$^

vlg: $(MAIN)
	valgrind --leak-check=yes --track-origins=yes ./$^

clean:
	rm $(OBJS) $(MAIN)
