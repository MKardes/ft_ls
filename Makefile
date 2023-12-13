NAME = ft_ls
CC = gcc
LIBFT = Libft/libft.a
F_LIBFT = Libft

FLAGS = -Wall -Wextra -Werror -ILibft -IHead
SRCS = Srcs/main.c

all: $(NAME)

$(NAME) : $(LIBFT) $(SRCS)
	$(CC) $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)
	@echo "\nFt_LS compiled successfully"

$(LIBFT): $(F_LIBFT)
	make bonus -C $(F_LIBFT)
	@echo "\nLibft Done"

clean:
	make clean -C $(F_LIBFT)

fclean: clean
	make fclean -C $(F_LIBFT)
	rm -rf $(NAME)

re: fclean all

.PHONY: clean re fclean all