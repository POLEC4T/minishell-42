/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/11 15:23:32 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cmd
{
	char	**args;
}			t_cmd;

void		msg(char *str1, char *str2, char *str3, int fd);
void		ft_putstr_fd(char *s, int fd);
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_strlen(char *str);
void		minishell();
char		*ft_strdup(char *s1);
char		*ft_strjoin(char *s1, char *s2);
char        **ft_split(char const *s, char *delim);
int			pos_in_str(char *str, char c);

#endif
