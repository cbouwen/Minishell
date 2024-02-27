/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:12 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/27 17:55:13 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirect_pipes(t_token *token) // maybe rethink name == function to parse the COMPLETE first command line  LEFT of the syntax tree
{
	t_token		*parent;

	while (token->type != PIPE)
		token = token->next;
	parent = token;
	reset_list(token);
	token->parent = parent;
	parent->left = token;
	parent = token;
	token = token->next;
//	redirect_right(token);//write pls          +       maybe write in main function of parser instead of here
	while (token->type != PIPE)
	{
		token->parent = parent;
		parent->right = token;
		parent = token;
		token = token->next;
	}
	reset_list(token);
}

int	redirect_right(t_token *token, int pipes) // rethink name
{
	t_token		*parent;

	while (token->type != PIPE)
			token = token->next;
	parent = token;
	token = token->next; //We need to add something to get to get past the first '|'. Use 'int pipes'
	while (token->type != PIPE)
	{
		token->parent = parent;
		parent->right = token;
		parent = token;
		if (token->next == NULL)
			break;
		token = token->next;
	}	
	pipes--;
	return (pipes);
}

int     pipe_counter(t_token *tmp)
{
    int pipes;

    pipes = 0;
    while (tmp)
    {
        if (tmp.type == PIPE)
            pipes++;
		if (tmp->next == NULL)
			break;
        tmp = tmp->next;
    }
    return (pipes)
}

int parser(t_token **tokens)
{
	int	pipes;

	pipes = pipe_counter(*tokens);
	reset_list(tokens);
	parse_pipes(*tokens)
	reset_list(tokens);
	if (pipes)
	{	
		redirect_pipes(*tokens); //first redirect?
		reset_list(tokens);
		while (pipes != 0)
			pipes = redirect_right(*tokens, pipes);
	}
	else
		redirect_right(*tokens, 0); //how does function behave with pipes = 0?

}

/*
int parser(t_token **tokens)
{
   t_token      *tmp;
   t_token      *first_token;
   int          pipes;

    pipes = pipe_counter(tmp);
    first_token = *tokens;
    tmp = *tokens;
    parse_pipes(tmp, head);
    tmp = first_token;
    parse_redirects(tmp, head, pipes);
    tmp = first_token;
    parse_commands(tmp, head);
    tmp = first_token;
    parse_arguments(tmp, head);
    tmp = first_token;
    return (1);
}*/
