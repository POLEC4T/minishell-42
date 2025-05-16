/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/16 11:05:45 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_word(char *buf, int pos, int max, const char *src)
{
	while (*src && pos < max)
		buf[pos++] = *src++;
	return (pos);
}

static int	handle_string(char *buf, int pos, const char *fmt, va_list args)
{
	char	*s;

	fmt += 2;
	s = va_arg(args, char *);
	if (!s)
		s = "(null)";
	pos = copy_word(buf, pos, 1023, s);
	return (pos);
}

int	ft_fprintf(int fd, const char *fmt, ...)
{
	char	buf[1024];
	int		pos;
	va_list	args;

	pos = 0;
	va_start(args, fmt);
	ft_memcpy(buf, "pitishell: ", 12);
	pos += 12;
	while (*fmt && pos < 1023)
	{
		if (*fmt == '%' && *(fmt + 1) == 's')
		{
			pos = handle_string(buf, pos, fmt, args);
			fmt += 2;
		}
		else
			buf[pos++] = *fmt++;
	}
	va_end(args);
	buf[pos] = '\0';
	if (write(fd, buf, pos) < 0)
		return (-1);
	return (pos);
}
