/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:25:13 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/29 19:28:05 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	pipe_decider(t_token **tokens, t_env *env, t_args *args)
{
	t_env	*temp_env;
	t_args	*temp_args;
	int		status;

	status = 0;
	temp_env = env;
	temp_args = args;
	if (count_consecutive_cats(*tokens))
		printf("cool_cat\n");
		//cool_cat(tokens, env, args);
	else
		status = run_piped_cmd(tokens, temp_env, temp_args);
	return (pipe_error_handler(status));
}

int	run_piped_cmd(t_token **tokens, t_env *env, t_args *args)
{
	pid_t	pid;

	args->in_fd = 0;
	args->pipe_count = count_pipes(*tokens);
	while (args->pipe_count >= 0)
	{
		pipe(args->fd);
		pid = fork();
		if (pid == 0)
			exit(real_pipe(*tokens, env, args));
		else if (pid < 0)
			return (3);
		else
		{
			wait(NULL);
			close(args->fd[1]);
			if (args->in_fd != 0)
				close(args->in_fd);
			args->in_fd = args->fd[0];
		}
		move_to_next(tokens);
		args->pipe_count--;
	}
	return (0);
}

int	real_pipe(t_token *tokens, t_env *env, t_args *args)
{
	int	status;
	t_token	*temp;
	t_env	*temp_env;
	t_args	*temp_args;

	status = 0;
	temp = tokens;
	temp_env = env;
	temp_args = args;
	if (temp_args->in_fd != 0)
	{
		dup2(temp_args->in_fd, 0);
		close(temp_args->in_fd);
	}
	if (temp_args->pipe_count > 0)
		dup2(temp_args->fd[1], 1);
	close(temp_args->fd[0]);
	status = run_cmd(temp, temp_env, temp_args);
	return (status);
}

int	run_cmd(t_token *tokens, t_env *env, t_args *args)
{
	t_token	*temp;
	t_env	*temp_env;
	t_args	*temp_args;
	int		status;

	temp = tokens;
	temp_env = env;
	temp_args = args;
	status = 0;
	status = run_basic_cmd(temp, temp_env, temp_args);
	free_args(temp_args);
	return (status);
}
