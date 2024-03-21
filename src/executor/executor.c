/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:42 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/21 20:52:22 by mlegendr         ###   ########.fr       */
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
	int				status;
	t_args			*args;

	temp = tokens;
	temp_env = env;
	status = 0;
	args = malloc(sizeof(t_args));
	if (!args)
		return (ft_error("executor: malloc error\n", 12));
	if (fill_env(args, temp_env) != 0)
		return (ft_error("executor: fill_env error\n", 1));
	while (temp)
	{
		if (temp->type == CMD)
		{
			if (fill_args(args, temp) != 0)
				return (ft_error("executor: fill_args error\n", 1));
			printf_args_env(args);
			if (ft_strcmp(temp->str, "echo") == 0)
				determine_echo(temp);
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
			else
				status = execve_executor(temp, args);
		}
		temp = temp->next;
	}
	free_args(args);
	return (status);
}

int _executor(t_token *tokens, t_environment *env)
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
		return (ft_error("executor: fill_env error\n", 1));
	if (check_pipes(temp) == 1)
	{
		printf("run_basic_cmd\n");
		run_basic_cmd(temp, temp_env, args);
	}
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

	temp = tokens;
	temp_env = env;
	status = 0;
	if (fill_args(args, temp) != 0)
		return (ft_error("run_basic_cmd: fill_args error\n", 1));
	printf_args_env(args);
	int debug = determine_builtin(temp);
	printf("determine_builtin: %d\n", debug);
	status = exec_syntax_check(temp, temp_env);
	printf("exec_syntax_check: %d\n", status);
	if (status == 0)
	{
		if (check_redirects(temp) == 1)
			//status = exec_command(temp, temp_env);
			printf("exec_command\n");
		else
			//status = redirect(temp, temp_env);
			printf("redirect\n");
	}
	return (1);
}
