NAME = ft_ls

CFLAGS := -Wall -Wextra -Werror -pedantic 
INC_DIR := inc
SRC_DIR := src
OBJ_DIR := obj

SRC_FILES := parse_flags.c main.c
SRCS := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

debug:
	@echo "SRCS = $(SRCS)"
	@echo "OBJS = $(OBJS)"

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "$(NAME) compiled successfully"

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
