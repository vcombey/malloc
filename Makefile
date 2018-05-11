CC = gcc

### MAIN FLAGS ###

APPEND=
DEBUG=
ASAN=

ifeq ($(DEBUG),yes)
	ASAN=-fsanitize=address
endif

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LIBRARY = libft_malloc_$(HOSTTYPE).so

NAME = libft_malloc.so

CFLAGS = -Wall -Wextra -Werror -g3 -O0 $(ASAN)

### SOURCES ###

SRC_CORE = malloc priority_queue zone_reference utils chunck allocator show_alloc sift show_alloc_large_zone reallocator desallocator
SRC_DIR = srcs

OBJ_DIR = objs

SRCS = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_CORE)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_CORE)))

#TMP = $(basename $(notdir $(SRC_CORE)))
#OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(TMP)))

IFLAGS = -I ./include/
LDFLAGS = -L ./libft -lft

.PHONY: all clean fclean re help test

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	echo $(SRCS)
	$(CC) $(CFLAGS) -shared -o $(LIBRARY) $(OBJ) $(IFLAGS)
	ln -s $(LIBRARY) $(NAME)

test:
	gcc -o ptest0 test/ptest0.c $(IFLAGS)  -L. -lft_malloc -I include
	gcc -o ptest1 test/ptest1.c $(IFLAGS)  -L. -lft_malloc -I include
	gcc -o ptest2 test/ptest2.c $(IFLAGS)  -L. -lft_malloc -I include
	gcc -o test0 test/test0.c $(IFLAGS)  -L. -lft_malloc -I include
	gcc -o test1 test/test1.c $(IFLAGS) -L. -lft_malloc -I include
	gcc -o test2 test/test2.c $(IFLAGS) -L. -lft_malloc -I include
	gcc -o test3 test/test3.c $(IFLAGS) -L. -lft_malloc  -I include
	gcc -o test3_2 test/test3_2.c $(IFLAGS) -L. -lft_malloc  -I include
	gcc -o test4 test/test4.c $(IFLAGS) -L. -lft_malloc  -I include
	gcc -o test5 test/test5.c $(IFLAGS) -L. -lft_malloc -I include
	gcc -o test6 test/test6.c $(IFLAGS) -L. -lft_malloc -I include
	gcc -o test7 test/test7.c $(IFLAGS) -L. -lft_malloc -I include

test_shared:
	gcc -o test0 shared_test/test0.c $(IFLAGS) -I include
	gcc -o test1 shared_test/test1.c $(IFLAGS) -I include
	gcc -o test2 shared_test/test2.c $(IFLAGS) -I include
	gcc -o test3 shared_test/test3.c $(IFLAGS) -I include
	gcc -o test4 shared_test/test4.c $(IFLAGS) -I include
	gcc -o test5 shared_test/test5.c $(IFLAGS) -I include
	gcc -o test6 shared_test/test6.c $(IFLAGS) -I include

test_clean:
	rm -f test*

$(OBJ_DIR):
	mkdir -p objs

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(IFLAGS) $(APPEND)

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
