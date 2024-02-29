/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:12 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/29 14:00:00 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirect_pipes(t_token *token, int pipes) //first redirect? We have a left here.
{
	t_token		*parent;
	(void)pipes;

	while (token->type != PIPE)
		token = token->next;
	parent = token;
	reset_list(&token);
	token->parent = parent;
	parent->left = token;
	parent = token;
	redirect_no_pipes(token); //rethink name
}

void	redirect_no_pipes(t_token *token) //rethink name
{
	t_token	*parent;

	while (token)
	{
		parent = token;
		if (token->next == NULL)
			break;
		token = token->next;
		if (token->type == PIPE)
			break;
		parent->right = token;
		token->parent = parent;
	}	
	reset_list(&token);
}

int     pipe_counter(t_token *tmp)
{
    int pipes;

    pipes = 0;
    while (tmp)
    {
        if (tmp->type == PIPE)
            pipes++;
		if (tmp->next == NULL)
			break;
        tmp = tmp->next;
    }
	reset_list(&tmp);
    return (pipes);
}

int parser(t_token **tokens)
{
	int	pipes;

	pipes = pipe_counter(*tokens);
	parse_pipes(*tokens);
	if (pipes)
	{
		redirect_pipes(*tokens, pipes);

	}
	else
		redirect_no_pipes(*tokens);
	return (1);
}
