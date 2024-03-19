/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:42 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/19 19:52:30 by mlegendr         ###   ########.fr       */
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
	execve_executor(temp);
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

/*int _executor(t_token *tokens, t_environment *env)
{
	t_token			*temp;
	t_environment	*temp_env;
	int				status;

	temp = tokens;
	temp_env = env;
	if (check_pipes(temp) == 1)
		status = run_basic_cmd(temp, temp_env);
	else
		status = run_piped_cmd(temp, temp_env);
	return (ft_error(NULL, status));
}

int run_basic_cmd(t_token *tokens, t_environment *env)
{
	t_token			*temp;
	t_environment	*temp_env;
	int				status;

	temp = tokens;
	temp_env = env;
	status = exec_syntax_check(temp, temp_env);
	if (status == 0)
	{
		if (check_redirects(temp) == 1)
			status = exec_command(temp, temp_env);
		else
			status = redirect(temp, temp_env);
	}
	return (ft_error(NULL, status));
}*/
