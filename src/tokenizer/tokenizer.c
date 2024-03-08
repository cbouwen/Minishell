/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:33:36 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/08 16:30:16 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_addtoken_toback(t_token **token, t_token *new)
{
	t_token	*temp;

	if (!token || !new)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	temp = *token;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}


t_token	*create_token(char *input)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(input);
	new->type = UNDEFINED;
	new->input = 0;
	new->output = 1;
	new->has_space = false;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	set_bool_to_true(t_token **tokens)
{
	while (*tokens)
	{
		if ((*tokens)->next == NULL)
			break;
		(*tokens) = (*tokens)->next;
	}
	(*tokens)->has_space = true;
	reset_list(tokens);
}

int	tokenizer(char *input, t_token **tokens)
{
	size_t	i;
	size_t	j;
	char	*tokenstr;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	while (input[i])
	{
		j = find_token(input, i);
		tokenstr = ft_strndup(input + i, j);
		if (!tokenstr)
			return (0);
		ft_addtoken_toback(tokens, create_token(tokenstr));
		i = i + j;
		free(tokenstr);
		while (input[i] && input[i] == ' ')
		{
			i++;
			set_bool_to_true(tokens);
		}
	}
	return (1);
}
