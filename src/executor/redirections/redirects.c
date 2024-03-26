/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:48:48 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/25 18:50:37 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	run_redirects(t_token *tokens, t_environment *env, t_args *args)
{
	t_token			*temp;
	t_environment	*temp_env;
	t_args			*temp_args;
	int				status;

	temp = tokens;
	temp_env = env;
	temp_args = args;
	status = 0;
	if (fill_args(args, temp) != 0)
		return (ft_error(NULL, 1));
	status = determine_redirect(temp, temp_args);
	status = determine_file(temp, temp_env, temp_args);
	if (temp_args->redirect == INPUT)
		status = redirect_input(temp, temp_env, temp_args);
	else if (temp_args->redirect == APPEND)
		status = redirect_append(temp, temp_env, temp_args);
	else if (temp_args->redirect == OUTPUT)
		status = redirect_output(temp, temp_env, temp_args);
	else if (temp_args->heredoc == 1)
		execute_command_with_heredoc(temp, temp_env, temp_args);
	return (ft_error(NULL, status));
}

int	redirect_input(t_token *tokens, t_environment *env, t_args *args)
{
	t_token			*temp;
	t_environment	*temp_env;
	t_args			*temp_args;
	int				saved_stdin;
	int				status;

	temp = tokens;
	temp_env = env;
	temp_args = args;
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return (ft_error("redirect: dup error\n", 1));
	if (dup2(temp_args->fd, STDIN_FILENO) == -1)
		return (ft_error("redirect: dup2 error\n", 1));
	close(temp_args->fd);
	status = prep_cmd(temp, temp_env, temp_args);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		return (ft_error("redirect: dup2 error\n", 1));
	close(saved_stdin);
	return (ft_error(NULL, status));
}

int	redirect_output(t_token *tokens, t_environment *env, t_args *args)
{
	t_token			*temp;
	t_environment	*temp_env;
	t_args			*temp_args;
	int				saved_stdout;
	int				status;

	temp = tokens;
	temp_env = env;
	temp_args = args;
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		return (ft_error("redirect: dup error\n", 1));
	if (dup2(args->fd, STDOUT_FILENO) == -1)
		return (ft_error("redirect: dup2 error\n", 1));
	close(args->fd);
	status = prep_cmd(temp, temp_env, temp_args);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (ft_error("redirect: dup2 error\n", 1));
	close(saved_stdout);
	return (ft_error(NULL, status));
}

int	redirect_append(t_token *tokens, t_environment *env, t_args *args)
{
	t_token			*temp;
	t_environment	*temp_env;
	t_args			*temp_args;
	int				saved_stdout;
	int				status;

	temp = tokens;
	temp_env = env;
	temp_args = args;
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		return (ft_error("redirect: dup error\n", 1));
	if (dup2(args->fd, STDOUT_FILENO) == -1)
		return (ft_error("redirect: dup2 error\n", 1));
	close(args->fd);
	status = prep_cmd(temp, temp_env, temp_args);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (ft_error("redirect: dup2 error\n", 1));
	close(saved_stdout);
	return (ft_error(NULL, status));
}
