MAKEFLAGS += --silent


CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

PTHEAD_FLAG = -lpthread

NAME = philo
NAME_BONUS = philo_bonus

SRCS_FILE =	./mandatory/srcs/philo.c \
			./mandatory/srcs/helpers.c	\
			./mandatory/srcs/utils.c\
			./mandatory/srcs/sleep.c

SRCS_FILE_BONUS = ./bonus/srcs/philo_bonus.c\
					./bonus/srcs/helpers_bonus.c\
					./bonus/srcs/utils_bonus.c\
					./bonus/srcs/sleep_bonus.c

OBJS = $(SRCS_FILE:.c=.o)

OBJS_BONUS = $(SRCS_FILE_BONUS:.c=.o)

make		:	$(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(PTHEAD_FLAG) $(OBJS) -o $(NAME) 


bonus : $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(PTHEAD_FLAG) $(OBJS_BONUS) -o $(NAME_BONUS)

clean:	
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean	:	clean
		$(RM) ./mandatory/$(NAME) ./bonus/$(NAME_BONUS)

re		:	fclean make

.PHONY	:	all clean fclean re

