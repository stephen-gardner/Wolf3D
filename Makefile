#!/usr/bin/make -f

################################################################################
# SETTINGS                                                                     #
################################################################################

NAME = wolf3d
CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3 -funroll-loops -march=native -pipe
FRAMEWORK = -framework OpenGL -framework AppKit
INC = -I inc -I libft/inc -I mlx/inc
LIBFT = libft/libft.a
MLX = mlx/libmlx.a
SRC_DIR = src
SRC = \
	load\
	movement\
	raycast\
	util\
	wolf3d
OBJ_DIR = $(SRC_DIR)/obj
OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(SRC))

################################################################################
# COLORS                                                                       #
################################################################################

NC = \033[0m
GREEN = \033[1;32m
RED = \033[1;31m
YELLOW = \033[1;33m

################################################################################
# RULES                                                                        #
################################################################################

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@printf "$(YELLOW)%-35s$(NC)" "Building $@... "
	@$(CC) $(CFLAGS) $(LIBFT) $(MLX) $(OBJ) $(FRAMEWORK) -o $@
	@echo "$(GREEN)DONE$(NC)"

$(LIBFT):
	@printf "$(YELLOW)%-35s$(NC)" "Building $@... "
	@make -C libft

$(MLX):
	@printf "$(YELLOW)%-35s$(NC)" "Building $@... "
	@make -C mlx

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo " > Compiling $<..."
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C libft clean
	@make -C mlx clean
	@echo "$(RED)Object files removed$(NC)"

fclean: clean
	@make -C libft fclean
	@make -C mlx fclean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) removed"

re: fclean all
