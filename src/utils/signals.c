/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:43:27 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/25 15:59:05 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sig_handler(int sig)
{
	//(void)sig;
	/*if (sig == SIGINT)
	{
		printf("\n");
		ft_error(NULL, 130);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		printf("\n");
		ft_error(NULL, 130);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}*/
	printf("\n");
	ft_error(NULL, 130);
	rl_replace_line("", 0);
	if (sig != SIGINT)
		rl_on_new_line();
	rl_redisplay();
}
