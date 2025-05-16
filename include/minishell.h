/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:53:03 by nle-gued          #+#    #+#             */
/*   Updated: 2025/05/16 15:38:42 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>

# define HD_FILENAME "heredoc_tmp_"

typedef enum e_redir_type
{
	IN,        // <
	HEREDOC,   // <<
	OUT_TRUNC, // >>
	OUT,       // >
	NONE
}					t_redir_type;

typedef struct s_redirect
{
	char			*filename;
	t_redir_type	redir_type;
	int				fd_in;
	int				fd_out;
}					t_redirect;

/**
 * cmd.exit_code is ONLY USED if the cmd failed to open a redir
 */
typedef struct s_cmd
{
	char			**args;
	t_redirect		**redirects;
	int				pid;
	int				exit_code;
}					t_cmd;

typedef struct s_key_value
{
	char			*key;
	char			*value;
}					t_key_value;

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef enum
{
	COMMAND,
	OPERATOR,
	PIPE,
	FLAG,
	ARGUMENT,
	FILES,
	// IN,
	// OUT,
	// HEREDOC,
	DELIMITER,
	NUL
}					token_type;

typedef struct s_token
{
	token_type		type;
	char			*data;
}					t_token;

typedef struct s_exec
{
	int				pipe_fds[2];
	int				prev_pipe_read;
	int				saved_stdout;
	int				saved_stdin;
}					t_exec;

typedef struct s_context
{
	t_node			**head_env;
	t_node			**head_cmd;
	t_exec			*exec_data;
	int				exit_code;
}					t_context;

void				minishell(char **envp);

// str
int					ft_putstr_fd(char *s, int fd);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_strlen(char *str);
char				*ft_strdup(char *s1);
char				*ft_strndup(const char *s, size_t n);
char				*ft_secure_strdup(t_context *ctx, char *s, char *err_title);
int					ft_strchr_idx(const char *s, int c);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_double_strjoin(char *s1, char *s2, char *s3);
char				**ft_split_first(char const *s, char *delim);
char				**ft_split(char const *s, char *delim);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
int					is_char_in_str(char c, char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
void				ft_free_tab(void **tab);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strchr(const char *string, int c);
size_t				ft_tablen(void **tab);
char				*ft_itoa(int n);

// output
int					ft_fprintf(int fd, const char *fmt, ...);

// lst
void				ft_lstadd_back(t_node **lst, t_node *new);
t_node				*ft_lstlast(t_node *lst);
t_node				*ft_lstnew(void *content);
void				ft_lstdelone(t_node *lst, void (*del)(void *));
void				ft_lstclear(t_node **lst, void (*del)(void *));
int					ft_lstsize(t_node *lst);
t_key_value			*cast_to_key_value(void *to_cast);
t_token				*cast_to_token(void *to_cast);
t_cmd				*cast_to_cmd(void *to_cast);

// env utils
t_key_value			*cast_to_key_value(void *to_cast);
t_node				*ft_envnew(char *key, char *value);
t_node				*ft_get_env_node(t_node **head, char *key);
char				*ft_get_env_val(t_context *ctx, char *key);
int					ft_set_env_val(t_node **head, char *key, char *value);
void				ft_free_env_content(void *content);
void				print_env_val(t_context *context, char *key);

// env
char				**env_to_tabstr(t_node **head_env);
void				create_or_set_env_var(t_context *context, char *key,
						char *value);
// builtins
int					ft_export(t_context *ctx, char **args);
void				ft_unset(t_context *ctx, char **args);
void				ft_env(t_node **head);
int					ft_cd(t_context *context, char **args);
int					cwd_error(char *to_free);
int					ft_pwd(char **args);
int					ft_echo(char **args);
void				ft_exit(t_context *context, char **args);
long long			ft_atoi_exit(const char *str_exit_code, int *error);
int					is_builtin_cmd(char *cmd);

// parsing
t_context			*read_token(t_context *ctx);
void				put_exec(char *str, t_node *token, char stop);
t_node				**parsing_init(char *str, t_context *ctx);
size_t				strcount(char *str, char stop);
int					define_token(t_node *node);
void				print_token_list(t_node *head);
t_cmd				*split_cmd(char *str, t_context *ctx);
char				*interpretation(char *str, t_context *ctx);
// utils pars
size_t				argslen(char *str);
size_t				redirlen(char *str);
size_t				skip_word(char *str, size_t i);
size_t				skip_redirection(char *str, size_t i);
size_t				skip_spaces(char *str, size_t i);
int					count_args(char *str);
int					count_redirect(char *str);
t_redirect			*redirect_define(char *str);
char				*args_define(char *str);
t_cmd				*cmd_initialize(size_t args_count, size_t redirects_count);
t_cmd				*initialize_cmd_with_counts(char *str);
size_t				handle_argument(char *str, size_t i, t_cmd *cmd,
						size_t *args);
size_t				handle_redirection(char *str, size_t i, t_cmd *cmd,
						size_t *redirect);

// syntax
int					syntax(t_node *head);
char				*quote_delimiter(char *str);

// free
void				exit_free(t_context *context);
void				free_context(t_context *context);
void				ft_free_ctx_cmds(t_context *context);
void				free_exec(t_exec *data);

// get_next_line
char				*get_next_line(int fd);

// TODO: delete
void				print_cmd(t_node *cmd);

////// pipex

# define READ 0
# define WRITE 1
# define BUFFER_SIZE 1024

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// exec
void				ft_exec(t_context *ctx);

// open_cmd_redirs
int					open_cmd_redirs(t_node *node_cmd);

// redirs
void				dup_cmd_redirs(t_context *ctx, t_node *node_cmd);

// exec_cmd
void				exec_cmd(t_context *ctx, t_node *node_cmd);

// init
void				clean_init_exec(t_context *ctx);

// output
void				msg(char *str1, char *str2, char *str3, int fd);

// close
void				close_pipes(t_exec *d);
void				my_close(int *fd);
void				close_all_cmds_redirs(t_node **head_cmd);
void				close_cmd_redirs(t_node *cmd_node);

// env check
char				*get_cmd_path(t_context *ctx, char *cmd);
char				**get_paths(t_context *ctx);

// utils
void				secure_fork(int *pid, t_context *ctx);
void				secure_pipe(t_context *ctx);
void				redirect(int input, int output, t_context *ctx);

// children
void				process_cmd(t_context *ctx, t_node *cmd);

// parent
void				start_children(t_context *ctx);
void				wait_children(t_context *ctx);

#endif