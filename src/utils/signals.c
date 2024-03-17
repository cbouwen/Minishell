/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:43:27 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/05 14:33:00 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_err;

void	sig_handler(int sig)
{
	(void)sig;
	printf("\n");
	g_err = 130;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();

}


