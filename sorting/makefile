# C compiler
CC = gcc

#compiler flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
CRELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

#includes
INCLUDES:= -I include

#libraries from -L../../lib
LFLAGS:= -L ./lib

#use libraries, like -lm
SECTION:= projects
SO_PREFIX:= lib
SO_SUFFIX:= .so
SO_NAME:= $(addprefix $(SO_PREFIX), $(addsuffix $(SO_SUFFIX), $(SECTION)))

#destinations
DEST_SO = ../lib
DS_INCLUDE_PATH:= include
GIT_INCLUDE_PATH:= ../include

DEPENDENCIES:= $(patsubst $(CURDIR)/src/%/, %, $(wildcard $(CURDIR)/src/*/))
H_FILES:= $(addsuffix .h, $(DEPENDENCIES))
# generic from here forward

.PHONY: all runall cleanall testall symlink vlg clean

#$(DEPENDENCIES):
#	$(CC) $(INCLUDES) -MM src/$@/$@.c

$(DEST_SO)/$(SO_NAME): $(addprefix obj/, $(addsuffix .o, $(DEPENDENCIES)))
	for dir in $^; do \
		ar rcs $@ $$dir; \
	done

symlink:
	for project in $(H_FILES); do \
		cd $(GIT_INCLUDE_PATH); \
		ln -fs ../sorting/$(DS_INCLUDE_PATH)/$$project $$project; \
		cd ../$(DS_INCLUDE_PATH); \
	done
all:
	for dir in $(DEPENDENCIES); do \
		$(MAKE) -C src/$$dir; \
	done

runall:
	for dir in $(DEPENDENCIES); do \
		$(MAKE) run -C src/$$dir; \
	done

cleanall:
	for dir in $(DEPENDENCIES); do \
		$(MAKE) clean -C src/$$dir; \
	done

testall:
	for dir in $(DEPENDENCIES); do \
		test/$$dir; \
	done

run-%:
	test/$*


$(DEST_OBJ)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

clean:
	rm $(DEST_SO)/$(SO_NAME)

# Print value of variable: https://stackoverflow.com/a/25817631/2374361
# e.g. make print-FOO
print-% :
	@echo $* = $($*)
