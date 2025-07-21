CC := cc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address

MLX_LIB := -lglfw3
MLXINCLUDE := -I ./MLX42/include -L ./MLX42
AMLX := ./MLX42/libmlx42.a

# MAC-specific linking
# MLX_FLAGS := -framework Cocoa -framework OpenGL -framework IOKit

# Linux-specific linking
MLX_FLAGS := -lglfw -ldl -lm -lX11 -lXrandr -lXcursor -lXi -lGL -pthread



RM := rm -f
NAME := cub3D
MANDO := mandatory
MANDO_SRC := ${MANDO}/src
MANDO_INC := ${MANDO}/include

UTILS_PATH := ${MANDO_SRC}/utils
PARSER_PATH := ${MANDO_SRC}/parser

# UTILS := ${UTILS_PATH}/ \

# PARSER := ${PARSER_PATH}/parser.c \

SRC := 	${UTILS} \
		${PARSER} \
		${MANDO_SRC}/cub3D.c \

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