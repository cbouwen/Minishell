/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:46:17 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/20 19:14:02 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_logic(t_token token, t_token next)//care for syntax error when comparing to 'next' when looking at last token
{
	t_token	previous;

	if (!previous)
		previous = NULL;
	if (previous == NULL && (token.type != ARG || token.type != CMD))
		return (0);
	if (token.type == PIPE && next.type != CMD)
		return (0);
	if (token.type == REDIRECT && next.type != ARG)
		return (0);
	previous = token;
	return (1);
}



int	check_syntax(t_token *tokens)
{
	while (*tokens)
	{
		if (!(check_logic(*tokens, *(tokens)->next)))
			return (0);
		tokens = tokens->next;
	}	
	return (1);
}


