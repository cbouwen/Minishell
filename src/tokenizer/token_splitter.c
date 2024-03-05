/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:23:28 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/05 15:35:10 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_redirect(char *input, size_t j, char c)
{
	size_t	i;

	i = j + 2;
	while (input[j] == c)
	{	
		j++;
		if (i == j)
			return (1);
	}
	return (0);
}

int	check_char(char c)
{
	if (c == 39 || c == '|' || c == '"' || c == '<' || c == '>')
		return (0);
	return (1);
}

size_t	handle_rest(char *input, size_t j)
{
	size_t	i;

	i = 0;
	while (input[i + j] && input[i + j] != ' ')
	{
		if (!(check_char(input[i + j])))
			return (i);
		i++;
	}
	return (i);
}


size_t	handle_quotes(char *input, size_t j, char c)
{
	size_t	i;

	i = 1;
	while (input[i + j] && input[i + j] != c)
		i++;
	if (input[i + j])
		i++;
	return (i);
}

size_t	find_token(char *input, size_t j)
{
	size_t	i;

	i = 0;
	if (handle_redirect(input, j, '<') || handle_redirect(input, j, '>'))
		return (2);
	if (input[j] == '|' || input[j] == '>' || input[j] == '<')
		return (1);
	if  (input[j] == 39)
	{
		i = handle_quotes(input, j, 39);
		return (i);
	}
	if  (input[j] == '"')
	{
		i = handle_quotes(input, j, '"');
		return (i);
	}
	i = handle_rest(input, j);
	return (i);
}
