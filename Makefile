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

NAME = libft_malloc_$HOSTTYPE.so

CFLAGS = -Wall -Wextra -Werror -g -O0 $(DEBUG)

### SOURCES ###

SRC_CORE = main malloc

VPATH = srcs

OBJ_DIR = objs
TMP = $(basename $(notdir $(SRC_CORE)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(TMP)))

IFLAGS = -I ./includes/
LDFLAGS = 

.PHONY: all clean fclean re help

all: $(NAME)

$(NAME): #$(OBJ)
	gcc -shared -o libft_malloc_$(HOSTTYPE).so srcs/malloc.c $(IFLAGS)
	ln -s libft_malloc_$(HOSTTYPE).so libft_malloc.so
	#$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

$(OBJ_DIR)/main.o: main.c
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/malloc.o: malloc.c
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
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
