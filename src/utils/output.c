/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/18 17:58:47 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
