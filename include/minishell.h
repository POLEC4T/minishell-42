/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:53:03 by nle-gued          #+#    #+#             */
/*   Updated: 2025/06/05 17:10:35 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define HD_FILENAME ".heredoc_tmp_"
# define READ 0
# define WRITE 1
# define BUFFER_SIZE 1024
# define UNDEFINED_INT -2
# define CHILD 0

extern int			g_signal;

/**
 *  IN					= <
 *	HEREDOC				= <<
 *	OUT_TRUNC			= >>
 *	OUT					= >
 *	HEREDOC_NO_INTER	= "eof"
 */
typedef enum e_redir_type
{
	IN,
	HEREDOC,
	OUT_TRUNC,
	OUT,
	HEREDOC_NO_INTER,
}					t_redir_type;

typedef enum e_inter_type
{
	HD,
	CMD,
}					t_inter_type;

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

typedef struct s_exec
{
	int				pipe_fds[2];
	int				prev_pipe_read;
	int				saved_stdout;
	int				saved_stdin;
}					t_exec;

typedef struct s_str_index
{
	size_t			i;
	char			*str;
}					t_str_index;

typedef struct s_context
{
	t_node			**head_env;
	t_node			**head_cmd;
	t_exec			*exec_data;
	int				exit_code;
	int				hd_pid;
	char			*rl_str;
}					t_context;

void				minishell(char **envp);

// str
int					ft_putstr_fd(char *s, int fd);
int					ft_putendl_fd(char *s, int fd);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_strlen(char *str);
char				*ft_strdup(char *s1);
char				*ft_strndup(const char *s, size_t n);
char				*ft_secure_strdup(t_context *ctx, char *s, char *err_title);
int					ft_strchr_idx(const char *s, int c);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_double_strjoin(t_context *ctx, char *s1, char *s2,
						char *s3);
char				*safe_ft_double_strjoin(t_context *ctx, char *s1, char *s2,
						char *s3);
char				**ft_split_first(char const *s, char *delim);
char				**ft_split(char const *s, char *delim);
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
char				*rm_last_char(char *str);
char				**ft_split_quote(char const *s, char *delim);
void				*return_free(void *to_free1, void *to_free2,
						void *to_free3);
int					return_int_failure_msg(char *msg);

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
t_cmd				*cast_to_cmd(void *to_cast);

// env utils
t_node				*ft_envnew(char *key, char *value);
t_node				*ft_get_env_node(t_node **head, char *key);
char				*ft_get_env_val(t_context *ctx, char *key);
void				ft_free_env_content(void *content);
t_key_value			*cast_to_key_value(void *to_cast);

// env
char				**env_to_tabstr(t_context *ctx, char *to_free);
void				create_or_set_env_var(t_context *context, char **kv);

// builtins
int					ft_export(t_context *ctx, char **args);
int					ft_unset(t_context *ctx, char **args);
int					ft_env(t_node **head);
int					ft_cd(t_context *context, char **args);
int					cwd_error(char *to_free);
int					ft_pwd(char **args);
int					ft_echo(char **args);
void				ft_exit(t_context *context, char **args);
long long			ft_atoi_exit(const char *str_exit_code, int *error);
int					is_builtin_cmd(char *cmd);

// parsing
int					parsing(char *str, t_context *ctx);
void				process_lines(t_context *ctx);
int					set_cmd_node_content(char *str, t_context *ctx,
						t_node *cmd_node);
size_t				extract_redirection_filename(char *str, char *filename);
int					handle_hd(t_context *ctx, char *str, size_t *i,
						t_redirect **redir);
int					count_dollars(const char *str);
int					has_dollar_preceded_by_redir(char *str, int i);
char				*get_unique_hd_filename(void);

// expand
char				*expand_line(char *str, t_context *ctx, int type);
int					find_end_inter(char *str, int type);
char				*get_expanded_str(char *str, char *inter, int final_len,
						int type);
void				update_quotes(char c, int *in_single, int *in_double);
int					should_expand(char *str, size_t i, int in_single);
char				*get_key_word(char *str);
void				skip_redir_word(const char *str, size_t *i, size_t *len);
int					get_final_len(char *str, char *keyword, int type);
int					has_dollar_preceded_by_redir(char *str, int i);
int					count_dollars(const char *str);

// utils pars
size_t				argslen(char *str);
size_t				redirlen(char *str);
size_t				skip_word(char *str, size_t i);
size_t				skip_redirection(char *str, size_t i);
size_t				skip_spaces(char *str, size_t i);
int					count_args(char *str);
int					count_redirect(char *str);
int					redirect_define(t_context *ctx, char *str,
						t_redirect **redir);
char				*args_define(char *str);
t_cmd				*init_cmd(size_t args_count, size_t redirects_count);
t_cmd				*initialize_cmd_with_counts(char *str);
size_t				handle_argument(char *str, size_t i, t_cmd *cmd,
						size_t *args);
size_t				handle_redirection(t_context *ctx, t_str_index *rl,
						t_cmd *cmd, size_t *i_redir);

// syntax
int					is_syntax_valid(char *str);

// signals
void				setup_child_signals(t_context *ctx);
void				setup_parent_signals(t_context *ctx);
int					setup_hd_signals(void);

// free
void				exit_free(t_context *context);
void				free_context(t_context *context);
void				free_ctx_cmds(t_context *context);
void				free_exec(t_exec *data);

// get_next_line
char				*get_next_line(int fd);

////// exec

// exec
void				ft_exec(t_context *ctx);
int					open_cmd_redirs(t_cmd *cmd);
void				dup_cmd_redirs(t_context *ctx, t_cmd *cmd);
void				exec_cmd(t_context *ctx, t_cmd *cmd);

// init
void				init_ctx_cmds(t_context *context);
void				init_context(t_context *ctx);

// close
void				close_exec_pipes(t_exec *d);
void				safe_close(int *fd);
void				close_all_cmds_redirs(t_node **head_cmd);
void				close_cmd_redirs(t_cmd *cmd);
void				close_exec_fds(t_exec *data);

// env check
char				*get_cmd_path(t_context *ctx, char *cmd);

// utils
void				secure_fork(int *pid, t_context *ctx);
void				secure_pipe(t_context *ctx);
void				redirect(int input, int output, t_context *ctx);

// children
void				process_cmd(t_context *ctx, t_cmd *cmd);

// parent
void				start_children(t_context *ctx);
void				wait_children(t_context *ctx);

#endif