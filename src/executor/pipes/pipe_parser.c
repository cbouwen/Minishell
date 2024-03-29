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

int run_piped_cmd(t_token **tokens, t_env *env, t_args *args)
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
}

int run_piped_execve(t_token *tokens, t_env *env, t_args *args)
{
    t_token	*temp;
    t_env	*temp_env;
    t_args	*temp_args;
    int		status;
    int     pipefd[2];  // File descriptors for the pipe

    temp = *tokens;
    temp_env = env;
    temp_args = args;
    status = 0;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    fill_args(temp, temp_args);
    assemble_path(temp_args);
    path_error_handler(temp_args->status);

    if (check_redirects(temp) == 1) {
        // Redirect the output of the current command to the input of the next command
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);  // Close write end of the pipe

        status = run_execve(args);

        // Redirect the input of the next command to the output of the current command
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);  // Close read end of the pipe
    } else {
        status = printf("run_redirect\n");
    }

    return (status);
}

int	prep_piped_execve(t_token *tokens, t_env *env, t_args *args)
{
	t_token	*temp;
	t_env	*temp_env;
	int		status;
	int		builtin;

	temp = tokens;
	temp_env = env;
	status = 0;
	
}*/

/*int	run_piped_builtin(t_token *tokens, t_env *env, t_args *args)
{
	t_token	*temp;
	t_env	*temp_env;
	t_args	*temp_args;
	int		status;

	temp = tokens;
	temp_env = env;
	temp_args = args;
	status = 0;
	temp_args->fd[1] = open("/tmp/pipe", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_args->fd[1] == -1)
		return (3);
	if (dup2(temp_args->fd[1], temp_args->fd[0]) == -1)
		return (4);
	run_builtin(temp, temp_env);
	if (dup2(temp_args->fd[0], temp_args->fd[1]) == -1)
		return (4);
	close(temp_args->fd[1]);
	return (status);







	if (check_redirects(temp) == 1)
		status = prep_cmd(temp, temp_env, NULL);
	else
		status = run_redirect(temp, temp_env, NULL);
	return (status);
}*/