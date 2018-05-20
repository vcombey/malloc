NAME = libft_malloc
CC = gcc
### MAIN FLAGS ###
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	ifeq ($(DEBUG),yes)
	CFLAGS = -std=c99 -fPIC -Wextra -Wall -Werror -g -O0 -fsanitize=address
else
	CFLAGS = -std=c99 -fPIC -Wextra -Wall -Werror -Ofast
endif
endif

ifeq ($(UNAME_S),Linux)
	ifeq ($(DEBUG),yes)
	CFLAGS = -std=c99 -fPIC -Wextra -Wall -Werror -g -O0 -fsanitize=address -D _POSIX_C_SOURCE=200809L
else
	CFLAGS = -std=c99 -fPIC -Wextra -Wall -Werror -Ofast -D _POSIX_C_SOURCE=200809L
endif
endif

### LIBRAIRIES ###

### SOURCES ###
MAIN = malloc priority_queue zone_reference utils chunck_large_zone allocator show_alloc sift show_alloc_large_zone reallocator desallocator size safe_alloc

SRC_LIST = $(MAIN)
VPATH = srcs include

## HEADERS
MAIN_HEADER = libft_alloc.h
_HEADERS = malloc.h
ifeq ($(HOSTTYPE),)
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif
SRC = $(addsuffix .c, $(SRC_LIST))
OBJ_DIR = objs
__OBJ__ = $(basename $(notdir $(SRC)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(__OBJ__)))
__H__ = $(basename $(notdir $(_HEADERS)))
HEADERS = $(addsuffix .h, $(__H__))
IFLAGS = -I ./include
ifeq ($(UNAME_S),Darwin)
	LDFLAGS = -shared -fPIC -exported_symbols_list symbol_list
endif
ifeq ($(UNAME_S),Linux)
	LDFLAGS = -shared -fPIC -Wl,--version-script=exportmap
endif

.PHONY: all clean fclean re help
all:  $(NAME).so

$(NAME).so: $(OBJ) symbol_list
	$(CC) $(CFLAGS) -o $(NAME)_$(HOSTTYPE).so $(OBJ) $(LDFLAGS)
	rm -f $(NAME).so
	ln -s libft_malloc_$(HOSTTYPE).so $(NAME).so

$(OBJ_DIR)/%.o: %.c $(HEADERS) Makefile
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ)
	rm -f $(NAME)_$(HOSTTYPE).so
	rm -f $(NAME).so

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
