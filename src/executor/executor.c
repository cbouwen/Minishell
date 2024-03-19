/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:42 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/19 18:55:10 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_err;

/*
	To Do:
		- Fix exit status, it has to reflect the bash exit status
			-- Maybe remove the strerror call for builtins?
		- Add syntax management for the builtins
		- Add function that pushes tokens to string array -- DONE
		- Add EXECVE
		- Add pipes
		- Add redirections
		- Test
*/

int	executor(t_token *tokens, t_environment *env) //change name to executor? along with the .c file?
{
	t_token			*temp;
	t_environment	*temp_env;
	//char 			**args;

	temp = tokens;
	temp_env = env;
	//print_args(token_to_string_array(temp));
	//args = token_to_string_array(temp);
	//run_execve(temp, args);
	execve_prep(temp);
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
