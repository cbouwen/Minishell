/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:07:23 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/04 18:26:54 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clean_exit(t_token *token, char *msg)
{
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	if (token)
		free_tokens(token);
	exit(0); //Als de error struct besta, kunnen we hier een deftige exit status meegeven. Nu is het gewoon exit succes.
}
