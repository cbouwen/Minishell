/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:53 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/05 16:59:57 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_quotes(t_token **tokens)
{
	int		i;
	int		j;
	char	*newstr;

	j = ft_strlen((*tokens)->str) - count_quotes((*tokens)->str);
	newstr = (char *)malloc(sizeof(char) * j + 1);
	if (!newstr)
		return ;
	i = 1;
	while ((*tokens)->str[i] && (*tokens)->str[i] != 39)
	{
		newstr[i - 1] = (*tokens)->str[i];
		i++;
	}
	newstr[i - 1] = '\0';
	free((*tokens)->str);
	(*tokens)->str = newstr;
}

void	expand_double_quote(t_token **tokens, t_environment *env)
{
	(void)env;

	remove_quotes(tokens);
}

static void	handle_quotes(t_token **tokens, t_environment *env)
{
	while (*tokens)
	{
		if ((*tokens)->type == ARG)
		{
			if (!(find_quote(*tokens, 39)))
				remove_quotes(tokens);
			if (!(find_quote(*tokens, '"')))
				expand_double_quote(tokens, env);
		}
		if ((*tokens)->next == NULL)
			break;
		(*tokens) = (*tokens)->next;
	}
	reset_list(tokens);
}


int	expander(t_token **tokens, t_environment *env)
{

	handle_quotes(tokens, env);
	handle_question_mark(tokens);
	return (1);
}

