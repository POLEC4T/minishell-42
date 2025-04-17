/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:24:18 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/17 14:07:03 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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

	struct s_token *previous;	
	token_type		type;
	char			*data;
	struct s_token	*next;
}					t_token;

// get_token(lst->content) => *t_token

void				maintest(void);
void				put_data(char *str, t_token *token, char stop);
t_token				*parsing(char *str);
size_t				strcount(char *str, char stop);
int					define_token(t_token token);

#endif