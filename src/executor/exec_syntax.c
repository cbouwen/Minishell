/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:24:56 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/25 19:00:26 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_syntax_check(t_token *tokens)
{
	t_token			*temp;
	int				status;

	temp = tokens;
	status = -1;
	if (tokens->type != CMD)
		return (ft_error("executor: syntax error\n", 1));
	if (determine_builtin(temp) == 1)
		status = 0;
	else if (determine_builtin(temp) == 2)
		status = 0;
	else if (determine_builtin(temp) == 3)
		status = check_env(temp);
	else if (determine_builtin(temp) == 4)
		status = check_export(temp);
	else if (determine_builtin(temp) == 5)
		status = check_unset(temp);
	else if (determine_builtin(temp) == 6)
		status = 0;
	else if (status == 2)
		status = 0;
	return (ft_error(NULL, status));
}

int	check_env(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (temp->next)
	{
		if (temp->next->type == ARG)
			return (ft_error("env: too many arguments\n", 127));
		else
			return (ft_error(NULL, 0));
	}
	return (ft_error(NULL, 0));
}

int	check_export(t_token *tokens)
{
	t_token	*temp;
	size_t		i;

	temp = tokens;
	i = count_tokens(temp);
	if (i == 1)
		return (ft_error("export: no input\n", 1));
	temp = temp->next;
	if (temp->has_space == 1)
		return (ft_error("export: not a valid identifier\n", 1));
	if (check_first_char(temp->str) == 1)
		return (ft_error("export: not a valid identifier\n", 1));
	if (i == 2)
	{
		if (check_last_char(temp->str, '=') == 1)
			return (ft_error("export: not a valid identifier\n", 1));
	}
	else
	{
		if (!temp->next)
			return (ft_error("export: not enough arguments\n", 1));
	}
	return (ft_error(NULL, 0));
}

/*if (!temp->next)
		return (ft_error("export: no input\n", 1));
	temp = temp->next;
	if (temp->has_space == 1)
		return (ft_error("export: not a valid identifier\n", 1));
	if (check_first_char(temp->str) == 1)
		return (ft_error("export: not a valid identifier\n", 1));
	if (!temp->next)
		return (ft_error("export: not enough arguments\n", 1));
	return (ft_error(NULL, 0));*/

int	check_unset(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (!temp->next)
		return (ft_error("unset: no input\n", 1));
	temp = temp->next;
	while (temp)
	{
		if (temp->type == ARG)
			if (check_first_char(temp->str) == 1)
				return (ft_error("unset: not a valid identifier\n", 1));
		temp = temp->next;
	}
	return (ft_error(NULL, 0));
}
