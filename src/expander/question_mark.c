/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question_mark.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:36:40 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/05 16:55:57 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_question_mark(t_token *token)
{
	char	*newstr;
	int	i;

	i = ft_strlen(token->str);
	newstr = ft_itoa(exit_status);
	if (!newstr)
		return (0);
	free(token->str);
	token->str = newstr; 
	return (1);
}

int	handle_question_mark(t_token **tokens)
{
	while (*tokens)
	{
		if ((*tokens)->type == ARG)
		{
			if (!(ft_strcmp((*tokens)->str, "$?")))
				execute_question_mark(*tokens);
		}
		if ((*tokens)->next == NULL)
			break;
		(*tokens) = (*tokens)->next;
	}
	reset_list(tokens);
	return (1);
}
