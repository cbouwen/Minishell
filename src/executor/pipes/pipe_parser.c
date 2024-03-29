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
    int     pipefd[2];
    pid_t   pid;

    temp = tokens;
    temp_env = env;
    (void)temp_env;
    temp_args = args;
    status = 0;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        close(pipefd[0]);  // Close unused read end
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
            return 1;
        }
        close(pipefd[1]);  // Close write end after it's duplicated

        status = fill_args(temp_args, temp);
        status = assemble_path(temp_args);
        path_error_handler(status);

        if (check_redirects(temp) == 1) 
        {
            status = run_execve(args);
        } 
        else
        {
            status = printf("run_redirect\n");
        }
        exit(status);  // Exit child process
    }
    else
    {
        // Parent process
        close(pipefd[1]);  // Close unused write end
        if (dup2(pipefd[0], STDIN_FILENO) == -1)
        {
            perror("dup2");
            return 1;
        }
        close(pipefd[0]);  // Close read end after it's duplicated
    }

    return (status);
}

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