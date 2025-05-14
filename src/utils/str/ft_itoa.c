/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:44:58 by mniemaz           #+#    #+#             */
/*   Updated: 2025/05/13 17:49:49 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		sign;

	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	n *= sign;
	i = count_digits(n);
	str = malloc(i + 1 + (sign < 0));
	if (!str)
		return (NULL);
	str[i + (sign < 0)] = '\0';
	while (i > 0)
	{
		str[--i + (sign < 0)] = n % 10 + '0';
		n /= 10;
	}
	if (sign < 0)
		str[0] = '-';
	return (str);
}
