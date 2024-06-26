/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:42 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/29 19:23:57 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	To Do:
		- Fix exit status, it has to reflect the bash exit status	--DONE
		- Add syntax management for the builtins					--DONE
		- Add function that pushes tokens to string array 			--DONE
		- Add function that pushes tokens to string array			--DONE
		- Add EXECVE												--DONE
		- Add pipes
		- Add redirections 											--ALMOST DONE
		- Add export support for test=value
		- Test
*/

int	builtin_executor(t_token *tokens, t_env *env, t_args *args)
{
	t_token	*temp;
	t_env	*temp_env;
	int		status;
	int		builtin;

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
		status = export_var(temp, temp_env);
	else if (builtin == 5)
		status = unset_var(temp->next, temp_env);
	else if (builtin == 6)
		status = change_dir(temp, temp_env);
	else if (builtin == 7)
		status = exit_shell(temp, temp_env, args);
	return (status);
}

int	executor(t_token *tokens, t_env *env)
{
	t_token	*temp;
	t_env	*temp_env;
	t_args	args;

	temp = tokens;
	temp_env = env;
	init_args(&args, temp, temp_env);
	if (fill_env(&args, temp_env) != 0)
		return (ft_error(NULL, 1));
	if (check_pipes(temp) == 1)
		run_basic_cmd(temp, temp_env, &args);
	else
		pipe_decider(&tokens, temp_env, &args);
	free_args(&args);
	return (1);
}

int	run_basic_cmd(t_token *tokens, t_env *env, t_args *args)
{
	t_token	*temp;
	t_env	*temp_env;
	t_args	*temp_args;
	int		status;

	temp = tokens;
	temp_env = env;
	temp_args = args;
	status = 0;
	if (check_redirects(temp) == 1)
		status = prep_cmd(temp, temp_env, temp_args);
	else
		status = run_redirect(temp, temp_env, temp_args);
	return (status);
}

int	run_builtin(t_token *tokens, t_env *env, t_args *args)
{
	t_token	*temp;
	t_env	*temp_env;
	int		status;

	temp = tokens;
	temp_env = env;
	status = exec_syntax_check(temp);
	if (status == 0)
		status = builtin_executor(temp, temp_env, args);
	return (ft_error(NULL, status));
}

int	prep_cmd(t_token *tokens, t_env *env, t_args *args)
{
	t_token	*temp;
	t_env	*temp_env;
	int		status;
	int		builtin;

	temp = tokens;
	temp_env = env;
	status = 0;
	builtin = determine_builtin(temp);
	if (args->arg_array == NULL)
	{
		if (fill_args(args, temp) != 0)
			return (ft_error(NULL, 1));
	}
	if (builtin != 0)
		status = run_builtin(temp, temp_env, args);
	if (builtin == 0)
	{
		status = assemble_path(args);
		status = path_error_handler(status);
		if (status == 2)
			status = run_execve(args);
	}
	return (status);
}
