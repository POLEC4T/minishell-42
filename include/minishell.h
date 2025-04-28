/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/28 16:09:47 by mniemaz          ###   ########.fr       */
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
# include <unistd.h>

typedef struct s_cmd
{
	char **args; // args contient tout les token de type COMMAND FLAG ARGUMENT
	int fd_in;   // init a -2 car -1 si erreur
	int				fd_out;
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
	IN,
	OUT,
	HEREDOC,
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
	int				**pipes;
	int				*pids;
	int				nb_cmds;
	char			**paths;
	char			*cmd_path;
}					t_exec;

typedef struct s_context
{
	t_node			**head_env;
	t_node			*head_token;
	t_node			**head_cmd;
	t_exec			*exec_data;
	int				exit_code;
}					t_context;

void				minishell(char **envp);

// str
void				ft_putstr_fd(char *s, int fd);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_strlen(char *str);
char				*ft_strdup(char *s1);
char				*ft_strndup(const char *s, size_t n);
int					ft_strchr_idx(const char *s, int c);
char				*ft_strjoin(char *s1, char *s2);
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
void				init_env(t_context *ctx, char **envp);
char				**env_to_tabstr(t_node **head_env);

// builtins
void				ft_export(t_context *ctx, char **args);
void				ft_unset(t_context *ctx, char **args);
void				ft_env(t_node **head);
void				ft_cd(t_context *context, char **args);
void				ft_pwd(char **args);
void				ft_echo(t_context *context, char **args);
void				ft_exit(t_context *context, char **args);
int					is_builtin_cmd(char *cmd);

// parsing
t_node				*read_token(t_context ctx);
void				put_exec(char *str, t_node *token, char stop);
t_node				*parsing(char *str);
size_t				strcount(char *str, char stop);
int					define_token(t_node *node);
void				print_token_list(t_node *head);

// syntax
int					syntax(t_node *head);
char				*quote_delimiter(char *str);

// free
void				exit_free(t_context *context);

// get_next_line
char				*get_next_line(int fd);

// TO DELETE
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

// init
void				init_exec(t_context *ctx);

// output
void				msg(char *str1, char *str2, char *str3, int fd);

// close
void				close_pipes(t_exec *d);
void				my_close(int *fd);
void				close_fds_cmds(t_node **head_cmd);

// env check
char				*get_cmd_path(t_context *ctx, char *cmd);
char				**get_paths(t_context *ctx);

// utils
void				secure_fork(int *pid, t_context *ctx);
char				**empty_split(void);
void				redirect(int input, int output, t_context *ctx);

// children
void				process_child(t_context *ctx, t_node *cmd, int i_cmds);

// parent
void				start_children(t_context *ctx);
int					wait_children(t_exec *d);

#endif