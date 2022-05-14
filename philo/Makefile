NAME = philo
CC = clang
HEADER = philosophers.h
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
SRCS = one.c clear.c check.c init.c main.c philo_utils.c print.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
