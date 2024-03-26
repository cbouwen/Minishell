/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:07:23 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/25 15:37:21 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_err;

void	clean_exit(t_token *token, t_environment *env, char *msg)
{
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	if (token)
		free_tokens(token);
	if (env)
		free_env(env);
	rl_clear_history();
	exit(g_err);
}
