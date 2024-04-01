/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:53 by cbouwen           #+#    #+#             */
/*   Updated: 2024/04/01 12:27:38 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_quotes(t_token **tokens, char c)
{
	int		i;
	int		j;
	char	*newstr;

	j = ft_strlen((*tokens)->str) - count_quotes((*tokens)->str, c);
	newstr = (char *)malloc(sizeof(char) * j + 1);
	if (!newstr)
		return ;
	i = 1;
	while ((*tokens)->str[i] && (*tokens)->str[i] != c)
	{
		newstr[i - 1] = (*tokens)->str[i];
		i++;
	}
	newstr[i - 1] = '\0';
	free((*tokens)->str);
	(*tokens)->str = newstr;
}

static void	handle_quotes(t_token **tokens, t_env *env)
{
	while (*tokens)
	{
		if ((*tokens)->type == ARG)
		{
			if (!(find_quote(*tokens, 39)))
			{
				remove_quotes(tokens, 39);
				break ;
			}
			if (!(find_quote(*tokens, '"')))
			{
				expand_double_quote(tokens, env);
				remove_quotes(tokens, '"');
			}
		}
		if ((*tokens)->next == NULL)
			break ;
		(*tokens) = (*tokens)->next;
	}
	reset_list(tokens);
}

static void	handle_metas(t_token **tokens, t_env *env)
{
	while (*tokens)
	{
		if ((*tokens)->type == ARG)
		{
			if ((*tokens)->str[0] == '$')
				(*tokens)->str = find_env((*tokens)->str, env);
		}
		if ((*tokens)->next == NULL)
			break ;
		(*tokens) = (*tokens)->next;
	}
	reset_list(tokens);
}

int	expander(t_token **tokens, t_env *env)
{
	handle_metas(tokens, env);
	handle_quotes(tokens, env);
	return (1);
}
