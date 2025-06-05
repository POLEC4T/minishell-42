/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_idx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:02:36 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/05 17:35:21 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief returns the index of the first occurrence of c in s
 * @details if c is not found, returns -1
 */
int	ft_strchr_idx(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (*(unsigned char *)(s + i) == (char)c)
			return (i);
	return (-1);
}
