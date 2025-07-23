CC := cc
CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g

MLX_LIB := -lglfw3
MLXINCLUDE := -I ./MLX42/include -L ./MLX42
AMLX := ./MLX42/libmlx42.a

# MacOS-specific linking
# MLX_FLAGS := -framework Cocoa -framework OpenGL -framework IOKit

# Linux-specific linking
MLX_FLAGS := -lglfw -ldl -lm -lX11 -lXrandr -lXcursor -lXi -lGL -pthread



RM := rm -f
NAME := cub3D
MANDO := mandatory
MANDO_SRC := ${MANDO}/src
MANDO_INC := ${MANDO}/include

UTILS_PATH := ${MANDO_SRC}/utils
PARSING_PATH := ${MANDO_SRC}/parsing
RENDERING_PATH := ${MANDO_SRC}/rendering

UTILS := ${UTILS_PATH}/ft_strcmp.c \
		 ${UTILS_PATH}/ft_strncmp.c \
		 ${UTILS_PATH}/ft_putstr_fd.c \
		 ${UTILS_PATH}/ft_strlen.c \
		 ${UTILS_PATH}/ft_strdup.c \
		 ${UTILS_PATH}/ft_substr.c \
		 ${UTILS_PATH}/ft_strtrim.c \
		 ${UTILS_PATH}/gnl.c \

PARSING := ${PARSING_PATH}/parsing.c \
		   ${PARSING_PATH}/parsing_utils.c \
		   ${PARSING_PATH}/identifiers_handling.c \

RENDERING := ${RENDERING_PATH}/rendering.c \
			 ${RENDERING_PATH}/rendering_utils.c \
			 ${RENDERING_PATH}/raycasting.c \

SRC := 	${UTILS} \
		${PARSING} \
		${RENDERING} \
		${MANDO_SRC}/cub3D.c \
		${MANDO_SRC}/cub3D_utils.c \

OBJS := ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${MANDO_INC}/cub3D.h
	${CC} ${CFLAGS} ${MLX_FLAGS} ${MLX_LIB} ${AMLX} ${MLXINCLUDE} ${OBJS} -o ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re