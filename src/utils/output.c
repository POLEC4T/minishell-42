/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/24 14:28:21 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_word(char *buf, int pos, int max, const char *src)
{
	while (*src && pos < max)
		buf[pos++] = *src++;
	return (pos);
}

int	ft_fprintf(int fd, const char *fmt, ...)
{
	char	buf[1024];
	int		pos;
	va_list	args;
	char	*s;

	pos = 0;
	va_start(args, fmt);
	ft_memcpy(buf, "pitishell: ", 12);
	pos += 12;
	while (*fmt && pos < 1023)
	{
		if (*fmt == '%' && *(fmt + 1) == 's')
		{
			fmt += 2;
			s = va_arg(args, char *);
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
