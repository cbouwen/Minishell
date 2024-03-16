/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:46:17 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/05 11:42:57 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_err	g_err;

int	check_logic(t_token tokens, int i)
{
	if (i == 0 && tokens.type == PIPE)
		return (0);
	if ((tokens.type == PIPE || tokens.type == REDIRECT) && tokens.next == NULL)
		return (0);
	if (tokens.next == NULL)
		return (1);
	if (tokens.type == PIPE && tokens.next->type != CMD)
		return (0);
	if (tokens.type == REDIRECT && tokens.next->type != ARG)
		return (0);
	return (1);
}



int	check_syntax(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (!(check_logic(*tokens, i)))
		{
			printf("Syntax error!\n");
			g_err.err = 2;
			g_err.type = OTHER;
			reset_list(&tokens);
			return (0);
		}
		i = 1;
		if (tokens->next == NULL)
			break;
		tokens = tokens->next;
	}
	reset_list(&tokens);	
	return (1);
}
