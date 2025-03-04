NAME = ft_ls

CFLAGS = -Wall -Wextra -Werror -pedantic -g
INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj

# libft paths
LIBFT_DIR = ./lib/libft
LIBFT_INC = $(LIBFT_DIR)/INC
LIBFT_A = $(LIBFT_DIR)/libft.a

# Source files
SRC_FILES = parse_flags.c main.c quicksort.c parse_paths.c print.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_INC) -c $< -o $@

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIBFT_DIR) -lft
	@echo "$(NAME) compiled successfully"

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
