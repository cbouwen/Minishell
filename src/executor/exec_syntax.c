/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:24:56 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/21 18:46:05 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int exec_syntax_check(t_token *tokens, t_environment *env)
{
	t_token			*temp;
	t_environment	*temp_env;
	int				status;

	temp = tokens;
	temp_env = env;
	status = 0;
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
	t_token *temp;

	temp = tokens;
	if (!temp->next)
		return (ft_error("export: no input\n", 1));
	if (check_last_char(temp->next->str) == 0)
		return (ft_error("export: not a valid identifier\n", 1));
	if (check_first_char(temp->next->str) == 1)
		return (ft_error("export: not a valid identifier\n", 1));
	if (!temp->next->next)
		return (ft_error("export: not enough arguments\n", 1));
	return (ft_error(NULL, 0));
}

int	check_unset(t_token *tokens)
{
	t_token *temp;

	temp = tokens;
	if (!temp->next)
		return (ft_error("unset: no input\n", 1));
	if (check_first_char(temp->next->str) == 1)
		return (ft_error("unset: not a valid identifier\n", 1));
	return (ft_error(NULL, 0));
}
