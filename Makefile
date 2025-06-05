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
LST_DIR = lst
BUILTINS_DIR = builtins
SIG_DIR = signals
INC_DIR = include
PARS_DIR = parsing
EXPAND_DIR = expand
EXEC_DIR = exec
SYNTAX_DIR = syntax
INITS_DIR = inits
CLOSE_DIR = close
CHILDREN_DIR = children
PARENT_DIR = parent
INCLUDES = -I$(INC_DIR)/

STR = $(addprefix $(STR_DIR)/, $(STR_FILES))
STR_FILES=\
	ft_memcpy.c \
	ft_strdup.c \
	ft_secure_strdup.c \
	ft_strndup.c \
	ft_strjoin.c \
	ft_double_strjoin.c \
	safe_double_strjoin.c \
	ft_strlen.c \
	ft_strlcpy.c \
	ft_strchr_idx.c \
	putstr_fd.c \
	putendl_fd.c \
	ft_split_first.c \
	ft_split_quotes.c \
	ft_split.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_strncmp.c \
	is_char_in_str.c\
	ft_calloc.c \
	ft_free_tab.c \
	ft_strchr.c \
	ft_fprintf.c \
	ft_itoa.c \
	ft_tablen.c \
	get_next_line.c \
	rm_last_char.c \
	return_free.c \
	return_int_failure_msg.c \

CLOSE = $(addprefix $(CLOSE_DIR)/, $(CLOSE_FILES))
CLOSE_FILES=\
	close_all_cmds_redirs.c \
	close_cmd_redirs.c \
	close_exec_pipes.c \
	safe_close.c \

ENV_UTILS = $(addprefix $(ENV_UTILS_DIR)/, $(ENV_UTILS_FILES))
ENV_UTILS_FILES=\
	env.c \
	env_to_tabstr.c \

FREE = $(addprefix $(FREE_DIR)/, $(FREE_FILES))
FREE_FILES=\
	free.c \
	free_utils.c \
	free_ctx_cmds.c \

INITS = $(addprefix $(INITS_DIR)/, $(INITS_FILES))
INITS_FILES=\
	inits.c \

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
	$(STR) \
	$(LST) \
	$(ENV_UTILS) \
	$(FREE) \
	$(CLOSE) \
	$(INITS) \

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

EXPAND = $(addprefix $(EXPAND_DIR)/, $(EXPAND_FILES))
EXPAND_FILES=\
	expand_line.c \
	expand_line_utils.c \
	expand_line_utils_str.c \

PARS = $(addprefix $(PARS_DIR)/, $(PARS_FILES))
PARS_FILES=\
	parsing.c \
	set_cmd_node_content.c \
	parsing_utils.c \
	count_utils.c \
	redir_utils.c \
	cmd_utils.c \
	handle_hd.c \
	get_unique_hd_filename.c \

PARENT = $(addprefix $(PARENT_DIR)/, $(PARENT_FILES))
PARENT_FILES=\
	start_children.c \
	wait_children.c \

CHILDREN = $(addprefix $(CHILDREN_DIR)/, $(CHILDREN_FILES))
CHILDREN_FILES=\
	process_cmd.c \
	dup_cmd_redirs.c \
	get_cmd_path.c \
	open_cmd_redirs.c \
	exec_cmd.c \

EXEC = $(addprefix $(EXEC_DIR)/, $(EXEC_FILES))
EXEC_FILES=\
	exec.c \
	utils.c \
	$(CHILDREN) \
	$(PARENT) \

SYNTAX = $(addprefix $(SYNTAX_DIR)/, $(SYNTAX_FILES))
SYNTAX_FILES=\
	syntax.c \

SIGNALS = $(addprefix $(SIG_DIR)/, $(SIGNALS_FILES))
SIGNALS_FILES=\
	signals.c \

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRC_FILES=\
	process_lines.c \
	main.c \
	$(UTILS) \
	$(BUILTINS) \
	$(PARS) \
	$(EXPAND) \
	$(SYNTAX) \
	$(EXEC) \
	$(SIGNALS) \

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