/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:42 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/14 16:36:37 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_err;

int	executor(t_token *tokens, t_environment *env) //change name to executor? along with the .c file?
{
	t_token			*temp;
	t_environment	*temp_env;

	temp = tokens;
	temp_env = env;
	while (temp)
	{
		if (temp->type == CMD)
		{
			if (ft_strcmp(temp->str, "echo") == 0)
			{
				if (temp->next && temp->next->type == ARG)
					echo(temp->right);
				else
					echo_no_arg(temp);
			}
			else if (ft_strcmp(temp->str, "pwd") == 0)
				pwd(temp);
			else if (ft_strcmp(temp->str, "env") == 0)
				print_env(temp, temp_env);
			else if (ft_strcmp(temp->str, "export") == 0)
				export_var(temp->next, temp_env);
			else if (ft_strcmp(temp->str, "unset") == 0)
				unset_var(temp->next, temp_env);
			else if (ft_strcmp(temp->str, "cd") == 0)
				change_dir(temp, temp_env);
		}
		temp = temp->next;
	}
	return (0);
}
