/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:46:16 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/17 13:38:45 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_tab(void **tab)
{
    int	i;

    if (!tab)
        return ;
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

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