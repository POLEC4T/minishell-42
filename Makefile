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
FREE_DIR = free
GNL_DIR = get_next_line
LST_DIR = lst
BUILTINS_DIR = builtins
INC_DIR = include
PARS_DIR = parsing
EXEC_DIR = exec
SYNTAX_DIR = syntax
CHILDREN_DIR = children
INCLUDES = -I$(INC_DIR)/

STR = $(addprefix $(STR_DIR)/, $(STR_FILES))
STR_FILES=\
	ft_memcpy.c \
	ft_strdup.c \
	ft_secure_strdup.c \
	ft_strndup.c \
	ft_strjoin.c \
	ft_strlen.c \
	ft_strlcpy.c \
	ft_strchr_idx.c \
	putstr_fd.c \
	ft_split_first.c \
	ft_split.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_strncmp.c \
	is_char_in_str.c\
	ft_calloc.c \
	ft_free_tab.c \
	ft_strchr.c \
	ft_itoa.c \
	ft_tablen.c \

ENV_UTILS = $(addprefix $(ENV_UTILS_DIR)/, $(ENV_UTILS_FILES))
ENV_UTILS_FILES=\
	env.c \
	env_to_tabstr.c \

FREE = $(addprefix $(FREE_DIR)/, $(FREE_FILES))
FREE_FILES=\
	free.c \


GNL = $(addprefix $(GNL_DIR)/, $(GNL_FILES))
GNL_FILES=\
	get_next_line.c \

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

UTILS = $(addprefix $(UTILS_DIR)/, $(UTILS_FILES))
UTILS_FILES=\
	output.c \
	$(STR) \
	$(LST) \
	$(ENV_UTILS) \
	$(FREE) \
	$(GNL) \

BUILTINS = $(addprefix $(BUILTINS_DIR)/, $(BUILTINS_FILES))
BUILTINS_FILES=\
	export.c \
	unset.c \
	env.c \
	cd.c \
	cd_utils.c \
	pwd.c \
	echo.c \
	exit.c \
	exit_utils.c \
	is_builtin_cmd.c

PARS = $(addprefix $(PARS_DIR)/, $(PARS_FILES))
PARS_FILES=\
	maintest.c \
	parsing.c \
	split_cmd.c \
	interpretation.c \
	parsing_utils.c \
	count_utils.c \
	redir_utils.c \
	cmd_utils.c \

CHILDREN = $(addprefix $(CHILDREN_DIR)/, $(CHILDREN_FILES))
CHILDREN_FILES=\
	process_cmd.c \
	dup_cmd_redirs.c \
	exec_cmd.c \

EXEC = $(addprefix $(EXEC_DIR)/, $(EXEC_FILES))
EXEC_FILES=\
	close.c \
	env_check.c \
	open_cmd_redirs.c \
	parent.c \
	exec.c \
	utils.c \
	$(CHILDREN) \

SYNTAX = $(addprefix $(SYNTAX_DIR)/, $(SYNTAX_FILES))
SYNTAX_FILES=\
	syntax.c \
	quote_delimiter.c \

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRC_FILES=\
	main.c \
	minishell.c \
	$(UTILS) \
	$(ENV) \
	$(BUILTINS) \
	$(PARS) \
	$(SYNTAX) \
	$(EXEC) \

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