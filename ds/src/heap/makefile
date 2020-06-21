# C compiler
CC = gcc

#compiler flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
CRELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

#includes
INCLUDES:= -I../../../include

#libraries from -L../../lib
LFLAGS:= -L../../lib

#use libraries, like -lm
LIB_PREFIX:= lib
LIB_NAME:= $(addprefix $(LIB_PREFIX), $(addsuffix .a, $(notdir $(CURDIR))))

#destinations
DEST_OBJ =../../obj
DEST_LIB = ../../lib
DEST_EXE = ../../test

#c sources
SRCS:= $(wildcard *.c)
LIB_DEPENDS:= dynamic_vector heapify
OTHER_DEPENDS:=
DEPEND_LIBS:= $(addprefix $(DEST_LIB)/$(LIB_PREFIX), $(addsuffix .a, $(LIB_DEPENDS)))
ALL_DEPENDS:= $(OTHER_DEPENDS) $(LIB_DEPENDS)

#obj files
OBJ_SRC:= $(addprefix $(DEST_OBJ)/, $(patsubst %.c, %.o, $(patsubst %_test.c, , $(SRCS))))
OBJ_TEST:= $(addprefix $(DEST_OBJ)/, $(patsubst %.c, %.o, $(wildcard *_test.c)))
OBJ_DEPENDS:= $(addprefix $(DEST_OBJ)/, $(patsubst %, %.o, $(OTHER_DEPENDS) $(LIB_DEPENDS)))

#exe name
MAIN:= $(addprefix $(DEST_EXE)/, $(notdir $(CURDIR)))

# generic from here forward

.PHONY: all run test vlg clean

$(DEST_LIB)/$(LIB_NAME): $(OBJ_SRC) $(OBJ_DEPENDS)
	ar rcs $@ $^

run: $(MAIN)
	for dir in $(ALL_DEPENDS); do \
		$(MAKE) -C ../$$dir; \
	done

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
