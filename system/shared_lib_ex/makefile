# C compiler
CC = gcc

#compiler flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
CRELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CUR_PATH:=/home/student/ezra-gordon/system/shared_lib_ex
RPATH:= -Wl,-rpath=$(CUR_PATH)

#includes
INCLUDES:= -I../../include

#libraries from -L../../lib
LFLAGS:= -L$(CUR_PATH)

#use libraries, like -lm
LIB_PREFIX:= lib
LIB_NAME:= $(addprefix $(LIB_PREFIX), $(addsuffix .a, bar))
SO1_NAME:= $(addprefix $(LIB_PREFIX), $(addsuffix .so, so1))
SO2_NAME:= $(addprefix $(LIB_PREFIX), $(addsuffix .so, so2))

#destinations
DEST_OBJ =../../obj
DEST_LIB = ../../lib
DEST_EXE = ../../test

#c sources
SRC_MAIN:= main.c
SRC_A:= $(wildcard a*.c)
SRC_SO1:= $(wildcard *so1.c)
SRC_SO2:= $(wildcard *so2.c)

#obj files
OBJ_A:= $(patsubst %.c, %.o, $(SRC_A))
OBJ_SO1:= $(patsubst %.c, %.o, $(SRC_SO1))
OBJ_SO2:= $(patsubst %.c, %.o, $(SRC_SO2))

#exe name
MAIN:= main

# generic from here forward

.PHONY: all run test vlg clean

$(LIB_NAME): $(OBJ_A)
	ar rcs $@ $^
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_A)
	$(CC) $(CFLAGS) -c -fPIC $(SRC_SO1)
	$(CC) $(CFLAGS) -c -fPIC $(SRC_SO2)
	$(CC) $(CFLAGS) -shared -o $(SO1_NAME) $(OBJ_SO1)
	$(CC) $(CFLAGS) -shared -o $(SO2_NAME) $(OBJ_SO2)
#$(OBJ_A):
#	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_A)
#	
#$(OBJ_SO1):
#	$(CC) $(CFLAGS) -c -fPIC $(SRC_SO1)
#	
#$(OBJ_SO2):
#	$(CC) $(CFLAGS) -c -fPIC $(SRC_SO2)
#
#$(SO1_NAME):
#	$(CC) $(CFLAGS) -shared -o $@ $(OBJ_SO1)
#	
#$(SO2_NAME):
#	$(CC) $(CFLAGS) -shared -o $@ $(OBJ_SO2)

run:
	$(CC) $(CFLAGS) $(RPATH) $(LFLAGS) -o $(MAIN) $(SRC_MAIN) $(SO1_NAME) $(LIB_NAME) -ldl
	
test: $(MAIN)
	./$^

vlg: $(MAIN)
	valgrind --leak-check=yes --track-origins=yes ./$^

clean:
	rm $(OBJ_A) $(OBJ_SO1) $(OBJ_SO2) $(LIB_NAME) $(MAIN) $(SO1_NAME) $(SO2_NAME)

# Print value of variable: https://stackoverflow.com/a/25817631/2374361
# e.g. make print-FOO
print-%:
	@echo $* = $($*)
