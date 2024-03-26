/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:07:23 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/26 14:16:52 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_signal g_signal;

void	clean_exit(t_token *token, char *msg)
{
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	if (token)
		free_tokens(token);
	exit(g_signal.err_no); //Als de error struct besta, kunnen we hier een deftige exit status meegeven. Nu is het gewoon exit succes.
}
