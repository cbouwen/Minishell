/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:56:08 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/27 13:35:40 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	define_cmd_arg(t_token *token, int i)
{
	if (i == 1 && token->type == UNDEFINED)
		token->type = ARG;
	if (i == 0 && token->type == UNDEFINED)
	{
		token->type = CMD;
		i = 1;
	}
	if (token->type == PIPE)
		i = 0;
	return (i);
}

void	define_metas(t_token *token)
{
	if (!(ft_strcmp(token->str, "|")))
		token->type = PIPE;
	if (!(ft_strcmp(token->str, "<")) || !(ft_strcmp(token->str, ">")))
		token->type = REDIRECT;
	if (!(ft_strcmp(token->str, "<<")) || !(ft_strcmp(token->str, ">>")))
		token->type = REDIRECT;
}


void	lexer(t_token **tokens)
{
	t_token	*tmp;
	int	start;

	start = 0;
	tmp = *tokens;
	while (tmp)
	{
		define_metas(tmp);
		tmp = tmp->next;
	}
	tmp = *tokens;
	while (tmp)
	{
		start = define_cmd_arg(tmp, start);
		tmp = tmp->next;
	}
	tmp = *tokens;
	if (!(check_syntax(tmp)))
		ft_error("Syntax Error\n");
//	tmp = *tokens;
}
