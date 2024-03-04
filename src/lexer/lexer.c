/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:56:08 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/27 15:29:14 by cbouwen          ###   ########.fr       */
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
	int	start;

	start = 0;
	while (*tokens)
	{
		define_metas(*tokens);
		if ((*tokens)->next == NULL)
			break;
		*tokens = (*tokens)->next;
	}
	reset_list(tokens);
	while (*tokens)
	{
		start = define_cmd_arg(*tokens, start);
		if ((*tokens)->next == NULL)
			break;
		*tokens = (*tokens)->next;
	}
	reset_list(tokens);
	if (!(check_syntax(*tokens)))
	{
		ft_error("Syntax Error\n");//implement something with the global variable so we can track exit statuses
	}
	reset_list(tokens);
}
