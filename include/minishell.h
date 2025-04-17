/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/17 14:09:48 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cmd
{
	char			**args;
}					t_cmd;

// typedef struct s_env_node
// {
// 	char				*key;
// 	char				*value;
// 	struct s_env_node	*next;
// }						t_node;

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

typedef struct s_context
{
	t_node			**head_env;
}					t_context;

void				minishell(char **envp);

// str
void				msg(char *str1, char *str2, char *str3, int fd);
void				ft_putstr_fd(char *s, int fd);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_strlen(char *str);
char				*ft_strdup_null(char *s1);
char				*ft_strjoin(char *s1, char *s2);
char				**ft_split_first(char const *s, char *delim);
int					is_char_in_str(char c, char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
void				ft_free_tab(void **tab);
void				*ft_calloc(size_t nmemb, size_t size);

// output
int					ft_fprintf(int fd, const char *fmt, ...);


// lst
void				ft_lstadd_back(t_node **lst, t_node *new);
t_node				*ft_lstlast(t_node *lst);
t_node				*ft_lstnew(void *content);
void				ft_lstdelone(t_node *lst, void (*del)(void *));
void				ft_lstclear(t_node **lst, void (*del)(void *));


void	maintest(void);
void					minishell(char **envp);


// env utils
t_key_value			*cast_to_key_value(void *to_cast);
t_node				*ft_envnew(char *key, char *value);
t_node				*ft_get_env(t_node **head, char *key);
int					ft_edit_env_val(t_node **head, char *key, char *value);
void				ft_free_env_content(void *content);
void				print_env(t_node **head);

// env
void				init_env(t_context *ctx, char **envp);

void				ft_export(t_context *ctx, t_key_value **args);

#endif
