# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 12:03:29 by noldiane          #+#    #+#              #
#    Updated: 2024/11/14 14:08:55 by noldiane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# INIT #

NAME = libft.a
DISPLAY = ✦ libft ✦

SRC_DIR = src/
OBJECTS_DIR = objects/

RM = rm -f
CC = gcc
CFLAGS += -Wall -Wextra -Werror

# SOURCES #

SOURCES = $(wildcard $(SRC_DIR)*.c)

OBJECTS += $(addprefix $(OBJECTS_DIR), $(notdir $(SOURCES:.c=.o)))

# COLORS #

BOLD=\033[1m
RESET=\033[0m

LIGHT_BLUE=\033[94m
LIGHT_CYAN=\033[96m
LIGHT_GREEN=\033[92m
LIGHT_YELLOW=\033[93m
LIGHT_ORANGE=\033[91m
LIGHT_PURPLE=\033[95m

CLASSIC_RED=\033[0;31m
CLASSIC_BLUE=\033[0;34m
CLASSIC_YELLOW=\033[0;33m
CLASSIC_GREEN=\033[0;32m

# OBJECT #

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

$(OBJECTS_DIR)%.o: %.c | $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

$(OBJECTS_DIR)%.o: $(SRC_DIR)%.c | $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

$(OBJECTS_DIR):
	mkdir -p $(OBJECTS_DIR)

clean:
	$(RM) -rf $(OBJECTS_DIR)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
