CC := cc
CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g
RM := rm -rf
NAME := cub3D

MANDO := bonus
MANDO_SRC := $(MANDO)/src
MANDO_INC := $(MANDO)/include
UTILS_PATH := $(MANDO_SRC)/utils
PARSING_PATH := $(MANDO_SRC)/parsing
RENDERING_PATH := $(MANDO_SRC)/rendering

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

RENDERING := $(RENDERING_PATH)/doors_and_animation_bonus.c \
             $(RENDERING_PATH)/draw_walls_bonus.c \
             $(RENDERING_PATH)/draw_walls_utils_bonus.c \
             $(RENDERING_PATH)/player_movments_bonus.c \
             $(RENDERING_PATH)/player_movments_utils_bonus.c \
             $(RENDERING_PATH)/raycast_bonus.c \
             $(RENDERING_PATH)/rendering_bonus.c \
             $(RENDERING_PATH)/rendering_utils_bonus.c

SRC := $(UTILS) \
       $(PARSING) \
       $(RENDERING) \
       $(MANDO_SRC)/cub3D_bonus.c \
       $(MANDO_SRC)/cub3D_utils.c

OBJS := $(SRC:.c=.o)

OS := $(shell uname -s)

ifeq ($(OS),Darwin)
    MLX_DIR := $(HOME)/Desktop/MLX42

    MLX_INCLUDE := -I$(MLX_DIR)/include
    MLX_LIB := -L$(MLX_DIR)/build

    BREW_GLFW := $(shell brew --prefix glfw 2>/dev/null)
    ifneq ($(BREW_GLFW),)
        MLX_LIB += -L$(BREW_GLFW)/lib
    else
        MLX_LIB += -L/opt/homebrew/opt/glfw/lib
    endif

    MLX_FLAGS := -lmlx42 -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
else ifeq ($(OS),Linux)
    MLX_INCLUDE := -I$(HOME)/Desktop/MLX42/include
    MLX_LIB := -L$(HOME)/Desktop/MLX42/build
    MLX_FLAGS := -lmlx42 -lglfw -ldl -lpthread -lm -lGL -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor
endif

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)
	@echo "Successfully built $(NAME)"

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(MLX_INCLUDE) -I$(MANDO_INC) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJS)

fclean: clean
	@echo "Removing executable..."
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
