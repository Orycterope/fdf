# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/18 19:13:31 by tvermeil          #+#    #+#              #
#    Updated: 2017/09/12 15:46:02 by tvermeil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory
NAME = fdf

SRC_PATH = src
HEADER_PATH = include/$(NAME)
ROOT = .
OBJ_FOLDER = obj/$(NAME)
INC_PATH = $(ROOT)/include/$(NAME) \
		   $(ROOT)/include/libft \

OBJ_PATH = $(ROOT)/$(OBJ_FOLDER)
DST_PATH = $(ROOT)
LFT_PATH = $(ROOT)

OS := $(shell uname)
ifeq ($(OS),Darwin)
	MLXLIBS = -lmlx -framework OpenGL -framework AppKit
else
	MLXLIBS = -lmlx -lXext -lX11
endif

CC = gcc -g3
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = $(addprefix -I ,$(INC_PATH))
LDFLAGS = -L$(LFT_PATH) -no-pie
LDLIBS = -lft -lm $(MLXLIBS)

SRC_NAME =		main.c \
				grid.c \
				parser.c \
				matrix.c \
				vector.c \
				display.c \
				camera.c \
				lines.c \
				colors.c \
				special_matrixes.c \

HEADER_NAME = 	fdf.h \
				matrix.h \
				display.h \
				camera.h \

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
DST = $(addprefix $(DST_PATH)/,$(NAME))
HEADER_FILES = $(addprefix $(HEADER_PATH)/,$(HEADER_NAME))

all: $(ROOT)/libft.a $(DST)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER_FILES) libft.a
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo -n .

$(DST): $(OBJ) $(HEADER_FILES)
	@$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(DST)
	@echo " . \033[32m$(NAME)\033[0m done"

libft.a:
	@make -C libft all
clean:
	@-cd $(ROOT) && rm -fv $(addprefix $(OBJ_FOLDER)/,$(OBJ_NAME))
	@rmdir $(OBJ_PATH) $(ROOT)/obj 2> /dev/null || true
	@make -C libft clean

fclean: clean
	@-cd $(DST_PATH) && rm -fv $(NAME)
	@make -C libft fclean

re: fclean all

ac: all clean

norme:
	@norminette $(SRC) $(HEADER_FILES)

.PHONY: all clean fclean re
