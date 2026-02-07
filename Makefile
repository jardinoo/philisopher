NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread -g
INCLUDES	= -I./include

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/init.c \
			  $(SRC_DIR)/routine.c \
			  $(SRC_DIR)/monitor.c \
			  $(SRC_DIR)/actions.c \
			  $(SRC_DIR)/utils.c \
			  $(SRC_DIR)/time.c \
			  $(SRC_DIR)/cleanup.c

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
