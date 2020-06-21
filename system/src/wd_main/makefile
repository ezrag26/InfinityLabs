# C compiler
CC = gcc

#compiler flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
CRELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

PATH_TO_LIB:= ../../lib
RPATH:= -Wl,-rpath=$(CUR_PATH)

#includes
WD_INCLUDES:= -I../../../include
DS_INCLUDES:= -I../../../include
INCLUDES:= -I../../../include

#libraries from -L../../lib
LFLAGS:= -L$(CUR_PATH)

#use libraries, like -lm
LIB_PREFIX:= lib
LIB_PATH:= ../../lib
LIB_NAME:= $(addprefix $(LIB_PATH)/, $(addprefix $(LIB_PREFIX), $(addsuffix .a, wd)))
WDSO_NAME:= $(addprefix $(LIB_PATH)/, $(addprefix $(LIB_PREFIX), $(addsuffix .so, wd)))

#destinations
DEST_OBJ = ../../obj
DEST_LIB = ../../lib
DEST_EXE = ../../test
WD_PATH = ../wd_main
WD_USER_PATH = ../watchdog_user

DS_SRC_PATH = ../../../ds/src
SCHED_PATH = ../../../scheduler_heap
DS_OBJ_PATH = ../../../ds/obj

OTHER = tasker uid dynamic_vector heap heapify
SCHED = scheduler_heap
WD_MAIN = wd_main
WD_USER = watchdog_user
EXE = wd

#c sources
SRC_WD_TEST:= wd_main_test.c
SRC_USER_TEST:= watchdog_user_test.c
SRC_DS:= $(addprefix $(DS_SRC_PATH)/, $(addsuffix .c, $(OTHER)))
SRC_SCHED:= $(addprefix $(SCHED_PATH)/, $(addsuffix .c, $(SCHED)))
SRC_WD:= $(addprefix $(WD_PATH)/, $(addsuffix .c, $(WD_MAIN)))
SRC_WD_USER:= $(addprefix $(WD_USER_PATH)/, $(addsuffix .c, $(WD_USER)))
#SRC_WDSO:= $(wildcard *so1.c)

#obj files
OBJ_OTHER:= $(addprefix $(DS_OBJ_PATH)/, $(addsuffix .o, $(OTHER) $(SCHED)))
OBJ_WD:= $(addprefix $(DEST_OBJ)/, $(addsuffix .o, $(wd)))
OBJ_WD_USER:= $(addprefix $(DEST_OBJ)/, $(addsuffix .o, $(WD_USER)))
#OBJ_WDSO:= $(patsubst %.c, %.o, $(SRC_WDSO))

#exe name
MAIN:= $(addprefix $(WD_USER)/, $(EXE))

# generic from here forward

.PHONY: all run test vlg clean

$(DEST_OBJ)/%.o: %.c
	$(CC) $(CFLAGS) $(WD_INCLUDES) $(RPATH) -fPIC -c -pthread $(SRC_DS) $(SRC_SCHED) $(SRC_WD) $(SRC_WD_USER) -o $@

$(WDSO_NAME): $(OBJ_OTHER) $(OBJ_WD) $(OBJ_WD_USER)
	$(CC) $(CFLAGS) -shared -o $@ $^


#$(OBJ_SCHED):
#	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_SCHED)
#
#$(OBJ_WDSO):
#	$(CC) $(CFLAGS) -c -fPIC #$(SRC_WDSO)
#
#$(WDSO_NAME):
#	$(CC) $(CFLAGS) -shared -o $@ #$(OBJ_WDSO)

run:
	$(CC) $(CFLAGS) $(RPATH) $(LFLAGS) -o $(MAIN) $(WDSO_NAME) $(LIB_NAME) -ldl

test: $(MAIN)
	./$^

vlg: $(MAIN)
	valgrind --leak-check=yes --track-origins=yes ./$^

clean:
	rm $(OBJ_SCHED) $(OBJ_WDSO) $(LIB_NAME) $(MAIN) $(WDSO_NAME)

# Print value of variable: https://stackoverflow.com/a/25817631/2374361
# e.g. make print-FOO
print-%:
	@echo $* = $($*)
