NAME		:= so_long

CC			:= cc
CFLAGS		:= -Werror -Wextra -Wall

# Directories
SRC_DIR		:= Srcs
INC_DIRS	:= . Includes mlx/minilibx-linux

# Add include paths (for local headers and MiniLibX headers)
CFLAGS		+= $(addprefix -I,$(INC_DIRS))

# Libft
LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

# MiniLibX (vendored)
MLX_DIR		:= mlx/minilibx-linux
MLX_LIB		:= $(MLX_DIR)/libmlx.a
# Linux link flags for MiniLibX
MLX_FLAGS	:= -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lz

# Sources
SRCS := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/read_map.c \
	$(SRC_DIR)/error_handling.c \
	$(SRC_DIR)/map_validation.c \
	$(SRC_DIR)/map_helpers.c \
	$(SRC_DIR)/counters.c \
	$(SRC_DIR)/start_game.c \
	$(SRC_DIR)/close_game.c \
	$(SRC_DIR)/end_game.c \
	$(SRC_DIR)/mlx_hook_helper.c \
	$(SRC_DIR)/sound.c \
	$(SRC_DIR)/rendering.c \
	$(SRC_DIR)/install_imgs.c \
	$(SRC_DIR)/img_helper.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: fclean all clean re
