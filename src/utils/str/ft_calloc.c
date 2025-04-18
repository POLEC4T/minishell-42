/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:36:46 by nle-gued          #+#    #+#             */
/*   Updated: 2025/04/18 16:37:09 by nle-gued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    ft_bzero(void *s, size_t n)
{
        unsigned char   *u_s;
        size_t                  i;

        u_s = s;
        i = 0;
        while (i < n)
        {
                u_s[i] = 0;
                i++;
        }
}

void    *ft_calloc(size_t nmemb, size_t size)
{
        void    *mem;

        if (size != 0 && nmemb > __SIZE_MAX__ / size)
                return (NULL);
        mem = malloc(nmemb * size);
        if (!mem)
                return (NULL);
        ft_bzero(mem, nmemb * size);
        return (mem);
}