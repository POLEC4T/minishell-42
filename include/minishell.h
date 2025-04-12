/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/12 14:17:41 by nle-gued         ###   ########.fr       */
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
	char				**args;
}						t_cmd;

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}						t_env_node;

typedef struct s_context
{
	t_env_node			*head_env;
}						t_context;

void					minishell(char **envp);

void					msg(char *str1, char *str2, char *str3, int fd);
void					ft_putstr_fd(char *s, int fd);
void					*ft_memcpy(void *dest, const void *src, size_t n);
int						ft_strlen(char *str);
char					*ft_strdup(char *s1);
char					*ft_strjoin(char *s1, char *s2);
char					**ft_split(char const *s, char *delim);
int						pos_in_str(char *str, char c);

t_env_node				*ft_lstnew(char *key, char *value);
void					ft_lstadd_back(t_env_node **head, t_env_node *new);

void					print_env(t_context *ctx);
void					init_env(t_context *ctx, char **envp);

#endif
