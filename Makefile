GREEN = \033[0;32m
RED = \033[0;31m
END = \033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
READLINE = -lreadline
OBJ_DIR = .obj
SRC_DIR = src
UTILS_DIR = utils
INC_DIR = include
INCLUDES = -I$(INC_DIR)/

UTILS = $(addprefix $(UTILS_DIR)/, $(UTILS_FILES))
UTILS_FILES=\
	str.c \
	ft_split.c \
	output.c \
	str2.c \

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRC_FILES=\
	main.c \
	minishell.c \
	$(UTILS) \


OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)
	@echo "$(GREEN)$(NAME) ready$(END)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(READLINE) -o $(NAME)
	@echo "Compiled $(NAME) successfully"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/minishell.h Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiled $<"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Cleaned up object files$(END)"

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@echo "$(RED)Cleaned up $(NAME) and object files$(END)"

debug:
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"

re: fclean all

.PHONY: all clean fclean re