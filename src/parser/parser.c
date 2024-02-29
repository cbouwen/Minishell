/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:12 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/29 18:17:00 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	first_redirect(t_token *token)
{
	t_token		*parent;

	while (token->type != PIPE)
		token = token->next;
	parent = token;
	reset_list(&token);
	token->parent = parent;
	parent->left = token;
	parent = token;
	redirect_right(token);
}

void	redirect_right(t_token *token)
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

int	redirect_others(t_token *token, int current_pipe)
{
	int	i;

	i = 1;
	while (token)
	{
		if (token->parent == NULL && token->type == PIPE)
			break;
		token = token->next;
	}
	while (token->left->type == PIPE)
	{
		if (i == current_pipe)
			break;
		token = token->left;
		i++;
	}
	redirect_right(token);
	return (--current_pipe);
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
	int	current_pipe;

	pipes = pipe_counter(*tokens);
	current_pipe = pipes;
	parse_pipes(*tokens);
	if (pipes)
	{
		first_redirect(*tokens);
		while (current_pipe != 0)
			current_pipe = redirect_others(*tokens, current_pipe);
	}
	else
		redirect_right(*tokens);
	return (1);
}
