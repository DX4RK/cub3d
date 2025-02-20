#.SILENT:

# INIT #

NAME = cub3D

INIT = START

SRC_DIR = src
LIBFT_DIR = libraries/libft
MINILIBX_DIR = libraries/minilibx
INCLUDE_DIR = include
OBJECTS_DIR = objects

START=$$(date +%s)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MINILIBX_DIR)
LDFLAGS = -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -lft -lmlx -lm -lX11 -lXext -pthread
RM = rm -f

# SOURCES #

SRCS = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJECTS_DIR)/%.o)

# COLORS #

BOLD=\e[1m
RESET=\e[0m
DIM	= "\e[2m"

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

# MAIN #

all: $(NAME)
	@echo "\n\t\t     $(BOLD)$(LIGHT_CYAN)$(NAME) is ready!$(RESET)"

$(NAME): $(INIT) $(OBJS) $(LIBFT_DIR)/libft.a $(MINILIBX_DIR)/libmlx.a
	@start=$$(date +%s)
	@echo "\t─────────────────────────────────────────"
	@echo "\t\t$(LIGHT_YELLOW)$(BOLD)    [BUILDING]$(RESET) $(NAME)..."
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@end=$$(date +%s)
	@echo "\t$(LIGHT_GREEN)$(BOLD)    [✓SUCCESS]$(RESET) built in $$((end - start)) seconds"
	@echo "\t─────────────────────────────────────────"

$(OBJECTS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(INIT):
	@echo "$(LIGHT_BLUE)"
	@echo "\t ██████ ██    ██ ██████  ██████  ██████  "
	@echo "\t██      ██    ██ ██   ██      ██ ██   ██ "
	@echo "\t██      ██    ██ ██████   █████  ██   ██ "
	@echo "\t██      ██    ██ ██   ██      ██ ██   ██ "
	@echo "\t ██████  ██████  ██████  ██████  ██████  "
	@echo "$(RESET)"

$(LIBFT_DIR)/libft.a:
	@start=$$(date +%s)
	@echo "\t─────────────────────────────────────────"
	@echo "\t\t$(LIGHT_YELLOW)$(BOLD)    [BUILDING]$(RESET) libft..."
	@$(MAKE) -s -C $(LIBFT_DIR) >/dev/null 2>&1
	@end=$$(date +%s)
	@echo "\t$(LIGHT_GREEN)$(BOLD)    [✓SUCCESS]$(RESET) built in $$((end - start)) seconds"

$(MINILIBX_DIR)/libmlx.a:
	@start=$$(date +%s)
	@echo "\t─────────────────────────────────────────"
	@echo "\t\t$(LIGHT_YELLOW)$(BOLD)    [BUILDING]$(RESET) minilibx..."
	@$(MAKE) -s -C $(MINILIBX_DIR)
	@end=$$(date +%s)
	@echo "\t$(LIGHT_GREEN)$(BOLD)    [✓SUCCESS]$(RESET) built in $$((end - start)) seconds"

clean:
	$(RM) -r $(OBJECTS_DIR) >/dev/null 2>&1
	@echo "$(LIGHT_ORANGE)$(BOLD)[CLEANED]$(RESET) OBJECTS"
	$(MAKE) clean -C $(LIBFT_DIR) >/dev/null 2>&1
	@echo "$(LIGHT_ORANGE)$(BOLD)[CLEANED]$(RESET) LIBFT"
	$(MAKE) clean -C $(MINILIBX_DIR)
	@echo "$(LIGHT_ORANGE)$(BOLD)[CLEANED]$(RESET) MINILIBX"
#
fclean: clean
	$(RM) $(NAME) >/dev/null 2>&1
	$(MAKE) fclean -C $(LIBFT_DIR) >/dev/null 2>&1
	@echo "$(LIGHT_PURPLE)$(BOLD)everything has been cleaned.$(RESET)"

re: fclean all

.SILENT:
.PHONY: all clean fclean re
