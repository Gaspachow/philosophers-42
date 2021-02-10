
SRCS	= main.c

SRCS	+= error_manager.c init.c utils.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo_one

CLANG	= clang

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= philo.h




all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME): $(OBJS)
	$(CLANG) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

%.o: %.c $(INCLUDE)
	$(CLANG) $(FLAGS) -c $<  -o $(<:.c=.o)
