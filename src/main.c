/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-gued <nle-gued@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by mniemaz           #+#    #+#             */
/*   Updated: 2025/04/12 14:50:48 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    // minishell(envp);
    maintest();
    return (EXIT_SUCCESS);
}