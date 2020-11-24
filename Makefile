CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = ft_select.c args.c secondary.c print.c signal.c keys.c errors.c

DIR = libft/libft.a

OBJS = $(SRCS:.c=.o)

NAME = ft_select

.PHONY: all
all: $(NAME)

$(NAME): $(DIR) $(OBJS)
	$(CC) $(OBJS) libft/libft.a -lcurses -ltermcap -o $(NAME)

$(DIR):
	# cd libft && $(MAKE)
	make -C libft

%.o: %.c ft_ls.h
	$(CC)  $< -c $(CFLAGS) -o $@

.PHONY: clean
clean:
	@rm -f $(OBJS)
	make -C libft/ clean

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)
	make -C libft/ fclean

.PHONY: re
re: fclean all
