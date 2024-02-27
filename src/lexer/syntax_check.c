/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:46:17 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/21 12:55:24 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_logic(t_token *tokens, int i)//care for syntax error when comparing to 'next' when looking at last token
{
	if (i == 0 && token.type == PIPE)
		return (0);
	if (token.type == PIPE && next.type != CMD)
		return (0);
	if (token.type == REDIRECT && next.type != ARG)
		return (0);
	return (1);
}



int	check_syntax(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
<<<<<<< HEAD
		if (!(check_logic(*tokens, i)))
=======
		if (!(check_logic(*tokens, *(tokens)->next)))
>>>>>>> 487c18e3f1b205a06a4111ead2c88958af974b1d
			return (0);
		i = 1;
		*tokens = *(tokens)->next;
	}	
	return (1);
}
