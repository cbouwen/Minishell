/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:24:56 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/21 16:59:55 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int exec_syntax_check(t_token *tokens, t_environment *env)
{
	t_token	*temp;
	t_environment	*temp_env;

	temp = tokens;
	temp_env = env;
	if (determine_builtin(temp) == 1)
		return (0);
	else if (determine_builtin(temp) == 2)
		return (0);
	else if (determine_builtin(temp) == 3)
		return (check_env(temp));
	else if (determine_builtin(temp) == 4)
		return (check_export(temp));
	/*else if (determine_builtin(temp) == 5)
		check_unset(temp, temp_env);
	else if (determine_builtin(temp) == 6)
		check_cd(temp, temp_env);*/
	return (1);
}

int	check_env(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (temp->next)
	{
		if (temp->next->type == ARG)
			return (134);
		else
			return (0);
	}
	return (0);
}

int	check_export(t_token *tokens)
{
	t_token *temp;

	temp = tokens;
	if (check_last_char(temp->next->str) == 0)
	{
		printf("export: %d\n", check_last_char(temp->next->str));
		return (134);
	}
	if (check_first_char(temp->next->str) == 1)
		return (134);	
	return (0);
}
