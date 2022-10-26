NAME = philosophers

CC = gcc -o
SRCS = $(wildcard ./srcs/*/*.c) $(wildcard ./srcs/*.c) 
OBJS = $(SRCS:.c=.o)
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address

%.o	:	%.c
	@gcc $(CFLAGS) -c $^ -I./ -o $@

all	:	$(NAME)

$(NAME): $(OBJS)
	@$(CC) $(NAME) $(OBJS) $(CFLAGS)

clean	:
	@rm -f $(OBJS)
	@echo -e "\033[41mObject Files Deleted \033[0m"
		
fclean	:	clean
	@rm -f $(NAME)
	@echo -e "\033[44mpush_swap Deleted \033[0m"

re			:	fclean all

.PHONY		:	all clean fclean re bonus