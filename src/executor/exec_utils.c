/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:31:53 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/25 18:52:39 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_pipes(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->type == PIPE)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	check_redirects(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIRECT)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	determine_builtin(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (ft_strcmp(temp->str, "echo") == 0)
		return (1);
	else if (ft_strcmp(temp->str, "pwd") == 0)
		return (2);
	else if (ft_strcmp(temp->str, "env") == 0)
		return (3);
	else if (ft_strcmp(temp->str, "export") == 0)
		return (4);
	else if (ft_strcmp(temp->str, "unset") == 0)
		return (5);
	else if (ft_strcmp(temp->str, "cd") == 0)
		return (6);
	return (0);
}

int	check_last_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == c)
		return (1);
	return (0);
}

int	check_first_char(char *str)
{
	if (ft_isdigit(str[0]) == 1)
		return (1);
	return (0);
}
