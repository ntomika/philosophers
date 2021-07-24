NAME		= philo_one

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

SRCS		= philo.c \
			threads.c \
			utilits.c \
			init.c

OBJS		= $(SRCS:.c=.o)

RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -I. $(CFLAGS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all