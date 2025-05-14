/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:02:34 by nle-gued          #+#    #+#             */
/*   Updated: 2024/11/11 20:45:43 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	manydigit(int n)
{
	int				count;
	unsigned int	ui;

	count = 1;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	ui = n;
	while (ui >= 10)
	{
		ui = ui / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*itoa;
	int				i;
	int				digit;
	unsigned int	ui;

	digit = manydigit(n);
	i = 0;
	itoa = malloc(manydigit(n) + 1);
	if (!itoa)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		itoa[i] = '-';
		i++;
	}
	ui = n;
	itoa[digit] = '\0';
	while (i < digit)
	{
		itoa[digit - 1] = (ui % 10) + 48;
		digit--;
		ui = ui / 10;
	}
	return (itoa);
}
/*
int	main(int argc, char **argv)
{
	int		test1;
	char	*res;

	res = ft_itoa(-2147483648);
	printf("%s", res);
}*/