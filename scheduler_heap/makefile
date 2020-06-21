# C compiler
CC = gcc

#compiler flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
CRELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

#includes
INCLUDES:= -I../include

#libraries from -L../../lib
LFLAGS:= -L../ds/lib

#use libraries, like -lm
LIB_PREFIX:= lib
LIB_NAME:= $(addprefix $(LIB_PREFIX), $(addsuffix .a, $(notdir $(CURDIR))))

#destinations
DEST_OBJ =../ds/obj
DEST_LIB = ../ds/lib
DEST_EXE = ../ds/test

#c sources
SRCS:= $(wildcard *.c)
LIB_DEPENDS:= heap
OTHER_DEPENDS:= uid tasker dynamic_vector heapify
DEPEND_LIBS:= $(addprefix $(DEST_LIB)/$(LIB_PREFIX), $(addsuffix .a, $(LIB_DEPENDS)))

#obj files
OBJ_SRC:= $(addprefix $(DEST_OBJ)/, $(patsubst %.c, %.o, $(patsubst %_test.c, , $(SRCS))))
OBJ_TEST:= $(addprefix $(DEST_OBJ)/, $(patsubst %.c, %.o, $(wildcard *_test.c)))
OBJ_DEPENDS:= $(addprefix $(DEST_OBJ)/, $(patsubst %, %.o, $(OTHER_DEPENDS) $(LIB_DEPENDS)))

#exe name
MAIN:= $(addprefix $(DEST_EXE)/, $(notdir $(CURDIR)))

# generic from here forward

.PHONY: all symlink run test vlg clean print-

$(DEST_LIB)/$(LIB_NAME): $(OBJ_SRC) $(OBJ_DEPENDS)
	ar rcs $@ $^

symlink:
	cd ../include; \
	ln -fs ../ds/include/scheduler_heap.h scheduler_heap.h;

run: $(MAIN)

$(MAIN): $(OBJ_SRC) $(OBJ_TEST) $(OBJ_DEPENDS)
	$(CC) $(CFLAGS) -o $@ $^

$(DEST_OBJ)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

test: $(MAIN)
	$^

vlg: $(MAIN)
	valgrind --leak-check=yes --track-origins=yes ./$^

clean:
	rm $(OBJ_SRC) $(OBJ_TEST) $(DEST_LIB)/$(LIB_NAME) $(MAIN)

# Print value of variable: https://stackoverflow.com/a/25817631/2374361
# e.g. make print-FOO
print-% :
	@echo $* = $($*)
