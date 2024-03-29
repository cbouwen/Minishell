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
	int		status;
	int		in_fd[2];

	status = 0;
	in_fd[0] = 0;
	in_fd[1] = count_pipes(*tokens) + 1;
	while (--in_fd[1] >= 0)
	{
		pipe(args->fd);
		pid_t pid = fork();
		if (pid == 0)
			exit(real_pipe(*tokens, env, args, in_fd));
		else if (pid < 0)
			return (3);
		else
		{
			wait(NULL);
			close(args->fd[1]);
			if (in_fd[0] != 0)
				close(in_fd[0]);
			in_fd[0] = args->fd[0];
		}
		move_to_next(tokens);
	}
	return (status);
}

int	real_pipe(t_token *tokens, t_env *env, t_args *args, int *in_fd)
{
	int	status;

	status = 0;
	if (in_fd[0] != 0)
	{
		dup2(in_fd[0], 0);
		close(in_fd[0]);
	}
	if (in_fd[1] > 0)
		dup2(args->fd[1], 1);
	close(args->fd[0]);
	status = run_piped_execve(tokens, env, args);
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