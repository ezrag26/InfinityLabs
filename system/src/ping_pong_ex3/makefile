# # C compiler
# CC = gcc
#
# #compiler flags
# CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
# CRELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
#
# #includes
# INCLUDES:= -I../../../include
#
# #libraries from -L../../lib
# LFLAGS:= -L../../lib
#
# #use libraries, like -lm
# LIB_PREFIX:= lib
# LIB_NAME:= $(addprefix $(LIB_PREFIX), $(addsuffix .a, $(notdir $(CURDIR))))
#
# #destinations
# DEST_OBJ =../../obj
# DEST_LIB = ../../lib
# DEST_EXE = ../../test
#
# #c sources
# P1:= ping_pong_ex3_p1
# P2:= ping_pong_ex3_p2
#
# C_P1:= $(addsuffix .c, $(P1))
# C_P2:= $(addsuffix .c, $(P2))
#
# #obj files
# OBJ_P1:= $(addprefix $(DEST_OBJ)/, $(patsubst %.c, %.o, $(C_P1)))
# OBJ_P2:= $(addprefix $(DEST_OBJ)/, $(patsubst %.c, %.o, $(C_P2)))
#
# #exe name
# EXEC_P1:= $(addprefix $(DEST_EXE)/, $(P1))
# EXEC_P2:= $(addprefix $(DEST_EXE)/, $(P2))
#
# # generic from here forward
#
# .PHONY: test2 test1 vlg clean
#
# $(EXEC_P1): $(C_P1)
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@
#
# $(EXEC_P2): $(C_P2)
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@
#
# test2: $(EXEC_P1)
# 	./$^&
#
# test1-%: $(EXEC_P2)
# 	./$^ $*
#
# vlg: $(MAIN)
# 	valgrind --leak-check=yes --track-origins=yes ./$^
#
# clean:
# 	rm $(EXEC_P1) $(EXEC_P2)
#
# # Print value of variable: https://stackoverflow.com/a/25817631/2374361
# # e.g. make print-FOO
# print-% :
# 	@echo $* = $($*)
