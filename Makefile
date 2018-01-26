CC = gcc

### MAIN FLAGS ###

APPEND=
ASAN=

ifeq ($(DEBUG),yes)
	DEBUG = -fsanitize=address
endif

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
LIBRARY = libft_malloc_$(HOSTTYPE).so

NAME = libft_malloc.so

CFLAGS = -Wall -Wextra -Werror -g -O0 $(DEBUG)

### SOURCES ###

SRC_CORE = main malloc

VPATH = srcs

OBJ_DIR = objs
TMP = $(basename $(notdir $(SRC_CORE)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(TMP)))

IFLAGS = -I ./includes/
LDFLAGS = 

.PHONY: all clean fclean re help test

all: $(NAME)

$(NAME): #$(OBJ)
	gcc -shared -o $(LIBRARY) srcs/malloc.c $(IFLAGS)
	ln -s $(LIBRARY) $(NAME)

#$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
test:
	gcc -o test0 test/test0.c -I includes
	gcc -o test1 test/test1.c -I includes
	gcc -o test2 test/test2.c -L. -lft_malloc  -I includes
	gcc -o test3 test/test3.c -I includes
	gcc -o test3_2 test/test3_2.c -I includes
	gcc -o test4 test/test4.c -I includes
	gcc -o test5 test/test5.c -L. -lft_malloc -I includes

test_clean:
	rm -f test*

$(OBJ_DIR)/main.o: main.c
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/malloc.o: malloc.c
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(LIBRARY)
	rm -f $(NAME)

re: fclean all

help:
	@echo
	@echo "Programm $(NAME)"
	@echo
	@echo "--------------------------------------------------------------------------"
	@echo " Disp rules."
	@echo
	@echo " all     : Compile the program $(NAME) into $(BINDIR) directory."
	@echo " re      : Recompile all objets of the programm."
	@echo " clean   : Remove objects."
	@echo " fclean  : Remove objects and programm."
	@echo " help    : Display this."
	@echo "--------------------------------------------------------------------------"
