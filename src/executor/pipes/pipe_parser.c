/*header pls*/

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
		status = printf("special case\n");
	else
		status = run_piped_cmd(tokens, temp_env, temp_args);
	return (pipe_error_handler(status));
}

/*int run_piped_cmd(t_token **tokens, t_env *env, t_args *args)
{
	t_token	*temp;
	t_env	*temp_env;
	t_args	*temp_args;
	int		status;
	int		pipe_count;

	temp = *tokens;
	temp_env = env;
	(void)temp_env;
	temp_args = args;
	status = 0;
	pipe_count = count_pipes(temp);
	while (pipe_count >= 0)
	{
		if (determine_builtin(temp) != 0)
			//status = run_piped_builtin(temp, temp_env, temp_args);
			status = printf("run_piped_builtin\n");
		else
			status = run_piped_execve(temp, temp_env, temp_args);
		move_to_next(tokens);
		pipe_count--;
	}
	return (status);
}*/

int	run_piped_cmd(t_token **tokens, t_env *env, t_args *args)
{
	//t_token	**temp;
	t_env	*temp_env;
	t_args	*temp_args;
	int		status;
	int		pipe_count;
	//int		fd[2];
	int		in_fd = 0;

	//temp = **tokens;
	temp_env = env;
	temp_args = args;
	status = 0;
	pipe_count = count_pipes(*tokens);
	while (pipe_count >= 0)
	{
		pipe(temp_args->fd);
		pid_t pid = fork();
		if (pid == 0)
		{
			if (in_fd != 0)
			{
				dup2(in_fd, 0);
				close(in_fd);
			}
			if (pipe_count > 0)
			{
				dup2(temp_args->fd[1], 1);
			}
			close(temp_args->fd[0]);
			status = run_piped_execve(*tokens, temp_env, temp_args);
			exit(status);
		}
		else if (pid < 0)
		{
			perror("fork");
			return -1;
		}
		else
		{
			wait(NULL);
			close(temp_args->fd[1]);
			if (in_fd != 0)
			{
				close(in_fd);
			}
			in_fd = temp_args->fd[0];
		}

		move_to_next(tokens);
		pipe_count--;
	}
	return (status);
}

int run_piped_execve(t_token *tokens, t_env *env, t_args *args)
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
	return (status);
}