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

SRC_CORE = malloc priority_queue zone_reference

VPATH = srcs

OBJ_DIR = objs
TMP = $(basename $(notdir $(SRC_CORE)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(TMP)))

IFLAGS = -I ./include/ -I ./libft/includes
LDFLAGS = -L ./libft -lft

.PHONY: all clean fclean re help test

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	echo lala
	gcc -shared -o $(LIBRARY) $@ $(IFLAGS)
	ln -s $(LIBRARY) $(NAME)

test:
	gcc -o test0 test/test0.c -L. -lft_malloc   -I includes
	gcc -o test1 test/test1.c -L. -lft_malloc   -I includes
	gcc -o test2 test/test2.c -L. -lft_malloc  -I includes
	gcc -o test3 test/test3.c  -L. -lft_malloc  -I includes
	gcc -o test3_2 test/test3_2.c  -L. -lft_malloc  -I includes
	gcc -o test4 test/test4.c  -L. -lft_malloc  -I includes
	gcc -o test5 test/test5.c -L. -lft_malloc -I includes

test_clean:
	rm -f test*

$(OBJ_DIR):
	mkdir -p objs

$(OBJ)%.o: $(VPATH)/$(SRC_CORE)%.c
	echo lol
	$(CC) $(CFLAGS) -c -o $@ $< $(IFLAGS)

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
