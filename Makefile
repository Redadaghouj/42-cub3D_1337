# Color Definitions
RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
RESET   := \033[0m

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g
RM := rm -rf
NAME := cub3D

# OS detection and MLX configuration
OS := $(shell uname -s)

# Path configurations
MANDO := mandatory
MANDO_SRC := $(MANDO)/src
MANDO_INC := $(MANDO)/include
UTILS_PATH := $(MANDO_SRC)/utils
PARSING_PATH := $(MANDO_SRC)/parsing
RENDERING_PATH := $(MANDO_SRC)/rendering

# Source files
UTILS := $(UTILS_PATH)/ft_strcmp.c \
         $(UTILS_PATH)/ft_strncmp.c \
         $(UTILS_PATH)/ft_putstr_fd.c \
         $(UTILS_PATH)/ft_strlen.c \
         $(UTILS_PATH)/ft_strdup.c \
         $(UTILS_PATH)/ft_substr.c \
         $(UTILS_PATH)/ft_strtrim.c \
         $(UTILS_PATH)/ft_split.c \
         $(UTILS_PATH)/ft_atoi.c \
         $(UTILS_PATH)/ft_isdigit.c \
         $(UTILS_PATH)/ft_strchr.c \
         $(UTILS_PATH)/gnl/get_next_line.c \
         $(UTILS_PATH)/gnl/get_next_line_utils.c

PARSING := $(PARSING_PATH)/parsing.c \
           $(PARSING_PATH)/parsing_utils.c \
           $(PARSING_PATH)/parse_identifiers.c \
           $(PARSING_PATH)/parse_rgb.c \
           $(PARSING_PATH)/parse_map.c \
           $(PARSING_PATH)/parse_map_utils.c

RENDERING := $(RENDERING_PATH)/rendering.c \
             $(RENDERING_PATH)/rendering_utils.c \
             $(RENDERING_PATH)/raycasting.c

SRC := $(UTILS) \
       $(PARSING) \
       $(RENDERING) \
       $(MANDO_SRC)/cub3D.c \
       $(MANDO_SRC)/cub3D_utils.c

OBJS := $(SRC:.c=.o)

# MLX42 configuration
MLX_DIR := ./MLX42
MLX_INCLUDE := -I$(MLX_DIR)/include
MLX_LIB := -L$(MLX_DIR)/build
AMLX := $(MLX_DIR)/build/libmlx42.a
QUIET := >/dev/null 2>&1

ifeq ($(OS),Darwin)
    MLX_FLAGS := -lmlx42 -lglfw -framework Cocoa -framework OpenGL -framework IOKit
    BREW_GLFW := $(shell brew --prefix glfw)
    MLX_LIB += -L$(BREW_GLFW)/lib
else ifeq ($(OS),Linux)
    MLX_FLAGS := -lmlx42 -lglfw -ldl -lpthread -lm -lGL -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor
endif

# Build rules
all: $(NAME)

$(NAME): $(AMLX) $(OBJS)
	@echo -e "$(GREEN)  Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)
	@echo -e "$(GREEN)  Successfully built $(NAME)$(RESET)"

$(AMLX):
	@echo -e "$(GREEN)  Building MLX42 library...$(RESET)"
	@mkdir -p $(MLX_DIR)/build
	@cd $(MLX_DIR) && cmake -B build $(QUIET) && cmake --build build $(QUIET)
	@echo -e "$(GREEN)  MLX42 library ready$(RESET)"

%.o: %.c
	@echo -e "$(GREEN)  Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(MLX_INCLUDE) -I$(MANDO_INC) -c $< -o $@

clean:
	@echo -e "$(RED)  Cleaning object files...$(RESET)"
	@$(RM) $(OBJS)
	@echo -e "$(GREEN)  Object files removed$(RESET)"

fclean: clean
	@echo -e "$(RED)  Removing executable...$(RESET)"
	@$(RM) $(NAME)
	@echo -e "$(RED)  Removing MLX42 build...$(RESET)"
	@$(RM) -r MLX42/build
	@echo -e "$(GREEN)  Full cleanup complete$(RESET)"

re: fclean
	@echo -e "$(YELLOW)  Rebuilding project...$(RESET)"
	@$(MAKE) all

.PHONY: all clean fclean re