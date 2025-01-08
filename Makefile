NAME = pipex

LIBDIR = libft
OBJDIR = obj
SRC = pipex.c utils.c
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
LIBFT = $(LIBDIR)/libft.a
CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@echo "Compilando $(NAME)..."
	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	@echo "Compilando libft..."
	$(MAKE) -C $(LIBDIR)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Limpando objetos..."
	rm -rf $(OBJDIR)
	$(MAKE) clean -C $(LIBDIR)

fclean: clean
	@echo "Removendo $(NAME)..."
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBDIR)

re: fclean all

.PHONY: all clean fclean re $(LIBFT)
