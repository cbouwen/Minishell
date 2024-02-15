/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:33:36 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/15 17:30:32 by cbouwen          ###   ########.fr       */
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
}


t_token	*create_token(char *input)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(input);
	new->type = UNDEFINED;
	new->next = NULL;
	//ft_addtoken_toback(token, new);
	return (new);
}

int	tokenizer(char *input, t_token **tokens)
{
	char	**args;
	int		i;

	args = split_args(input, ' ');//no handling of single or double quotation marks
	if (!args)
		return (0);
	i = 0;
	while (args[i])
	{
		ft_addtoken_toback(tokens, create_token(args[i]));
		//tokens = create_token(args[i], tokens);
		//error handling?
		i++;
	}
	ft_free(args, i);
	return (1);
}
