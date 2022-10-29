NAME = philosophers


CC = gcc
SRCS = $(wildcard ./srcs/*/*.c) $(wildcard ./srcs/*.c) 
OBJS = $(SRCS:.c=.o)
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=thread
INC = philo.h

all	:	$(NAME)


$(NAME): $(OBJS) $(INC)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

%.o	:	%.c
	@gcc $(CFLAGS) -c $^ -I./ -o $@

clean	:
	@rm -f $(OBJS)
	@echo -e "\033[41mObject Files Deleted \033[0m"

fclean	:	clean
	@rm -f $(NAME)
	@echo -e "\033[44mpush_swap Deleted \033[0m"

re			:	fclean all

.PHONY		:	all clean fclean re bonus