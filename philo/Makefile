NAME = philo
SRC = main.c init.c safe_functions.c error.c utils.c extract_data.c status.c \
		simulation.c simulation_utils.c set_get.c eat.c think.c free.c
SRC_FILES = $(addprefix src/, $(SRC))
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
INCLUDE = -I./include -I./libft
LINKING = -Llibft -lft

all: $(NAME)

$(NAME): $(SRC_FILES)
	make -C ./libft
	$(CC) $(INCLUDE) $(CFLAGS) $(SRC_FILES) -o $(NAME) $(LINKING)

clean:
	make -C ./libft clean
	$(RM) *.o

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME)

re: fclean all

.PHOMY: all clean fclean re
