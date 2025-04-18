/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/12 20:17:02 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @details using a buffer in order to write every strs in one putstr
 */
void	msg(char *str1, char *str2, char *str3, int fd)
{
	char	buffer[1024];
	int		len1;
	int		len2;
	int		len3;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	len3 = ft_strlen(str3);
	if (7 + len1 + len2 + len3 + 1 > 1024)
	{
		ft_putstr_fd("minishell: msg: buffer overflow\n", STDERR_FILENO);
		return ;
	}
	ft_memcpy(buffer, "minishell: ", 7);
	ft_memcpy(buffer + 7, str1, len1);
	ft_memcpy(buffer + 7 + len1, str2, len2);
	ft_memcpy(buffer + 7 + len1 + len2, str3, len3);
	buffer[7 + len1 + len2 + len3] = '\n';
	buffer[7 + len1 + len2 + len3 + 1] = '\0';
	write(fd, buffer, 7 + len1 + len2 + len3 + 1);
}

/* Copie src dans buf à partir de la position pos tant que pos < max.
 * Retourne la nouvelle position après copie.
 */
static int	copy_word(char *buf, int pos, int max, const char *src)
{
	while (*src && pos < max)
		buf[pos++] = *src++;
	return (pos);
}

int	ft_fprintf(int fd, const char *fmt, ...)
{
	char buf[1024];
	int pos = 0;
	va_list args;
	va_start(args, fmt);
	ft_memcpy(buf, "pitishell: ", 12);
	pos += 12;
	while (*fmt && pos < 1023)
	{
		if (*fmt == '%' && *(fmt + 1) == 's')
		{
			fmt += 2;
			char *s = va_arg(args, char *);
			if (!s)
				s = "(null)";
			pos = copy_word(buf, pos, 1023, s);
		}
		else
			buf[pos++] = *fmt++;
	}
	va_end(args);
	return (write(fd, buf, pos) < 0 ? -1 : pos);
}
