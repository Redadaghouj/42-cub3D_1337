# ==========================================
# ============ Color Definitions ===========
# ==========================================
RED     := \033[0;31m
GRN     := \033[0;32m
YEL     := \033[0;33m
BLUE    := \033[38;2;35;177;239m
RESET   := \033[0m

# ==========================================
# ============ Compiler Settings ===========
# ==========================================
CC      := cc
CFLAGS  := -Wall -Wextra -Werror #-fsanitize=address -g
RM      := rm -rf
NAME    := cub3D

# ==========================================
# ============ Mandatory Paths =============
# ==========================================
MANDO       := mandatory
MANDO_SRC   := $(MANDO)/src
MANDO_INC   := $(MANDO)/include

UTILS_PATH      := $(MANDO_SRC)/utils
PARSING_PATH    := $(MANDO_SRC)/parsing
RENDERING_PATH  := $(MANDO_SRC)/rendering

# ==========================================
# ============ Mandatory Sources ===========
# ==========================================
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

RENDERING := $(RENDERING_PATH)/draw_walls.c \
             $(RENDERING_PATH)/draw_walls_utils.c \
             $(RENDERING_PATH)/player_movements.c \
             $(RENDERING_PATH)/player_movements_utils.c \
             $(RENDERING_PATH)/raycast.c \
             $(RENDERING_PATH)/rendering.c

SRC  := $(UTILS) $(PARSING) $(RENDERING) $(MANDO_SRC)/cub3D.c
OBJS := $(SRC:.c=.o)

# ==========================================
# ============== Bonus Paths ===============
# ==========================================
BONUS       := bonus
BONUS_SRC   := $(BONUS)/src
BONUS_INC   := $(BONUS)/include

BONUS_UTILS_PATH     := $(BONUS_SRC)/utils
BONUS_PARSING_PATH   := $(BONUS_SRC)/parsing
BONUS_RENDERING_PATH := $(BONUS_SRC)/rendering

# ==========================================
# ============== Bonus Sources =============
# ==========================================
BONUS_UTILS := $(BONUS_UTILS_PATH)/ft_strcmp_bonus.c \
         $(BONUS_UTILS_PATH)/ft_strncmp_bonus.c \
         $(BONUS_UTILS_PATH)/ft_putstr_fd_bonus.c \
         $(BONUS_UTILS_PATH)/ft_strlen_bonus.c \
         $(BONUS_UTILS_PATH)/ft_strdup_bonus.c \
         $(BONUS_UTILS_PATH)/ft_substr_bonus.c \
         $(BONUS_UTILS_PATH)/ft_strtrim_bonus.c \
         $(BONUS_UTILS_PATH)/ft_split_bonus.c \
         $(BONUS_UTILS_PATH)/ft_atoi_bonus.c \
         $(BONUS_UTILS_PATH)/ft_isdigit_bonus.c \
         $(BONUS_UTILS_PATH)/ft_strchr_bonus.c \
         $(BONUS_UTILS_PATH)/gnl/get_next_line_bonus.c \
         $(BONUS_UTILS_PATH)/gnl/get_next_line_utils_bonus.c

BONUS_PARSING := $(BONUS_PARSING_PATH)/parsing_bonus.c \
           $(BONUS_PARSING_PATH)/parsing_utils_bonus.c \
           $(BONUS_PARSING_PATH)/parse_identifiers_bonus.c \
           $(BONUS_PARSING_PATH)/parse_rgb_bonus.c \
           $(BONUS_PARSING_PATH)/parse_map_bonus.c \
           $(BONUS_PARSING_PATH)/parse_map_utils_bonus.c

BONUS_RENDERING := $(BONUS_RENDERING_PATH)/draw_walls_bonus.c \
             $(BONUS_RENDERING_PATH)/draw_walls_utils_bonus.c \
             $(BONUS_RENDERING_PATH)/player_movements_bonus.c \
             $(BONUS_RENDERING_PATH)/player_movements_utils_bonus.c \
             $(BONUS_RENDERING_PATH)/raycast_bonus.c \
             $(BONUS_RENDERING_PATH)/rendering_bonus.c \
             $(BONUS_RENDERING_PATH)/doors_and_animation_bonus.c \
             $(BONUS_RENDERING_PATH)/draw_minimap_bonus.c \
             $(BONUS_RENDERING_PATH)/draw_minimap_utils_bonus.c

BONUS_SRC  := $(BONUS_UTILS) $(BONUS_PARSING) $(BONUS_RENDERING) $(BONUS_SRC)/cub3D_bonus.c
BONUS_OBJS := $(BONUS_SRC:.c=.o)

# ==========================================
# ============== MLX Settings ==============
# ==========================================
OS := $(shell uname -s)

MLX_DIR     := assets/MLX42
MLX_BUILD   := $(MLX_DIR)/build
MLX_LIB     := $(MLX_BUILD)/libmlx42.a
MLX_INCLUDE := -I$(MLX_DIR)/include

ifeq ($(OS),Darwin)
	LFLAGS := -framework Cocoa -framework OpenGL -framework IOKit -L /Users/$(shell basename $(HOME))/.brew/opt/glfw/lib -lglfw
else
	LFLAGS := -lglfw -lm -ldl -lGL
endif

# ==========================================
# =============== Rules ====================
# ==========================================
all: mlx $(NAME)

mlx:
	@printf "$(YEL)  Checking for MLX42...$(RESET)\n"
	@if [ ! -f $(MLX_LIB) ]; then \
		printf "$(YEL)  MLX42 not found, cloning and building...$(RESET)\n"; \
		$(RM) $(MLX_DIR); \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
		cd $(MLX_DIR) && cmake -B build && cmake --build build; \
	else \
		printf "$(GRN)  MLX42 already built$(RESET)\n"; \
	fi

$(NAME): $(OBJS) $(MLX_LIB) $(MANDO_INC)/cub3D.h $(MANDO_INC)/rendering.h $(MANDO_INC)/parsing.h
	@printf "$(GRN)  Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_INCLUDE) $(LFLAGS) -o $(NAME)
	@$(RM) $(BONUS_OBJS)
	@printf "$(GRN)  Successfully built $(NAME)$(RESET)\n"

bonus: mlx .bonus

.bonus: $(BONUS_OBJS) $(MLX_LIB) $(BONUS_INC)/cub3D_bonus.h $(MANDO_INC)/rendering_bonus.h $(MANDO_INC)/parsing_bonus.h
	@printf "$(GRN)  Linking bonus $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(MLX_LIB) $(MLX_INCLUDE) $(LFLAGS) -o $(NAME)
	@touch .bonus
	@$(RM) $(OBJS)
	@printf "$(GRN)  Successfully built $(NAME)$(RESET)\n"

# Generic compile rule
%.o: %.c
	@printf "$(BLUE)  Compiling $<...$(RESET)\n"
	@$(CC) $(CFLAGS) $(MLX_INCLUDE) -I$(MANDO_INC) -c $< -o $@

clean:
	@printf "$(RED)  Cleaning object files...$(RESET)\n"
	@$(RM) $(OBJS) $(BONUS_OBJS) .bonus
	@printf "$(GRN)  Object files removed$(RESET)\n"

fclean: clean
	@printf "$(RED)  Removing executable...$(RESET)\n"
	@$(RM) $(NAME)
	@printf "$(RED)  Removing MLX42...$(RESET)\n"
	@$(RM) $(MLX_DIR)
	@printf "$(GRN)  Full cleanup complete$(RESET)\n"

re: fclean all
	@printf "$(YEL)  Rebuilding project...$(RESET)\n"

re_bonus: fclean bonus
	@printf "$(YEL)  Rebuilding project...$(RESET)\n"

.PHONY: all clean fclean re bonus mlx
