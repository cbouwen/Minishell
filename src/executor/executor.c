/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:42 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/22 20:47:55 by mlegendr         ###   ########.fr       */
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

int	builtin_executor(t_token *tokens, t_environment *env)
{
	t_token			*temp;
	t_environment	*temp_env;
	int				status;
	int				builtin;

	temp = tokens;
	temp_env = env;
	status = 0;
	builtin = determine_builtin(temp);
	if (builtin == 1)
		status = determine_echo(temp);
	else if (builtin == 2)
		status = pwd(temp);
	else if (builtin == 3)
		status = print_env(temp, temp_env);
	else if (builtin == 4)
		status = export_var(temp->next, temp_env);
	else if (builtin == 5)
		status = unset_var(temp->next, temp_env);
	else if (builtin == 6)
		status = change_dir(temp, temp_env);
	else
		return (ft_error("executor: unexpected error\n", 1));
	return (status);
}

int executor(t_token *tokens, t_environment *env)
{
	t_token			*temp;
	t_environment	*temp_env;
	t_args			*args;

	temp = tokens;
	temp_env = env;
	args = malloc(sizeof(t_args));
	if (!args)
		return (ft_error("executor: malloc error\n", 12));
	if (fill_env(args, temp_env) != 0)
		return (ft_error(NULL, 1));
	if (check_pipes(temp) == 1)
		run_basic_cmd(temp, temp_env, args);
	else
		//status = run_piped_cmd(temp, temp_env);
		printf("run_piped_cmd\n");
	free_args(args);
	return (1);
}

int run_basic_cmd(t_token *tokens, t_environment *env, t_args *args)
{
	t_token			*temp;
	t_environment	*temp_env;
	int				status;
	int				builtin;

	temp = tokens;
	temp_env = env;
	status = 0;
	builtin = determine_builtin(temp);
	if (fill_args(args, temp) != 0)
			return (ft_error(NULL, 1));
	args->exec_path = ft_calloc(sizeof(char *), 1);
	if (!args->exec_path)
		return (ft_error("execve: calloc error\n", 12));
	//status = assemble_path(args);
	if (builtin != 0)
		status = run_builtin(temp, temp_env);
	else
	{
		status = assemble_path(args);
		if (status == 2)
			status = run_execve(args);
	}
	return (status);
}

int run_builtin(t_token *tokens, t_environment *env)
{
	t_token			*temp;
	t_environment	*temp_env;
	int				status;

	temp = tokens;
	temp_env = env;
	status = exec_syntax_check(temp);
	if (status == 0)
		status = builtin_executor(temp, temp_env);
	return (ft_error(NULL, status));
}
