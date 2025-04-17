GREEN = \033[0;32m
RED = \033[0;31m
END = \033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
DEP_FLAGS = -MMD -MP -MF
READLINE = -lreadline
BUILD_DIR = .build
OBJ_DIR = $(BUILD_DIR)/obj
DEP_DIR = $(BUILD_DIR)/dep
SRC_DIR = src
UTILS_DIR = utils
STR_DIR = str
ENV_UTILS_DIR = env_utils
LST_DIR = lst
BUILTINS_DIR = builtins
INC_DIR = include
PARS_DIR = parsing
INCLUDES = -I$(INC_DIR)/

STR = $(addprefix $(STR_DIR)/, $(STR_FILES))
STR_FILES=\
	str.c \
	ft_split_first.c \
	str2.c \
	str3.c \

ENV_UTILS = $(addprefix $(ENV_UTILS_DIR)/, $(ENV_UTILS_FILES))
ENV_UTILS_FILES=\
	env.c \

LST = $(addprefix $(LST_DIR)/, $(LST_FILES))
LST_FILES=\
	ft_lstaddback.c \
	ft_lstaddfront.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter_bonus.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c \
	cast.c \

# lst.c \

UTILS = $(addprefix $(UTILS_DIR)/, $(UTILS_FILES))
UTILS_FILES=\
	output.c \
	$(STR) \
	$(LST) \
	$(ENV_UTILS) \

BUILTINS = $(addprefix $(BUILTINS_DIR)/, $(BUILTINS_FILES))
BUILTINS_FILES=\
	export.c \
	unset.c \
	env.c \

PARS = $(addprefix $(PARS_DIR)/, $(PARS_FILES))
PARS_FILES=\
	maintest.c \
	parsing.c \
	put_data.c \
	define_token.c \

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRC_FILES=\
	main.c \
	minishell.c \
	$(UTILS) \
	$(ENV) \
	$(BUILTINS) \
	$(PARS) \


OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(patsubst $(SRC_DIR)/%.c, $(DEP_DIR)/%.d, $(SRCS))

all: $(NAME)
	@echo "$(GREEN)$(NAME) ready$(END)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(READLINE) -o $(NAME)
	@echo "Compiled $(NAME) successfully"

-include $(DEPS)
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c Makefile
	@dep_file_path=$(patsubst $(OBJ_DIR)/%.o,$(DEP_DIR)/%.d,$@); \
	mkdir -p $(dir $@); \
	mkdir -p $$(dirname $$dep_file_path); \
	$(CC) $(CFLAGS) $(INCLUDES) $(DEP_FLAGS) $$dep_file_path -c $< -o $@; \
	echo "Compiled $<"

clean:
	@rm -rf $(BUILD_DIR)
	@echo "$(RED)Removed build files$(END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Removed $(NAME)$(END)"

debug:
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "DEPS: $(DEPS)"

re: fclean all

.PHONY: all clean fclean re debug