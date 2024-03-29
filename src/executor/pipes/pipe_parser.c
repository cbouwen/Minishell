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
	temp_args = args;
	status = 0;
	pipe_count = count_pipes(temp);
	args->fd[0] = dup(STDOUT_FILENO);
	if (args->fd[0] == -1)
		return (2);
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
    t_token *temp;
    t_env *temp_env;
    t_args *temp_args;
    int status;
    int pipefd[2];
    pid_t pid;
    int fd_in = 0;  // The input for the first command is STDIN

    temp = tokens;
    temp_env = env;
    temp_args = args;
    (void)temp_env;
    status = 0;

    while (temp != NULL) {
        if (pipe(pipefd) == -1) {
            perror("pipe");
            return 1;
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        }

        fill_args(temp_args, temp);
        printf("temp_args->arg_array[0]: %s\n", temp_args->arg_array[0]);

        if (pid == 0) {
            // Child process
            dup2(fd_in, STDIN_FILENO);  // Change the input according to the old pipe
            if (temp->next != NULL)  // If there is another command
                dup2(pipefd[1], STDOUT_FILENO);  // Send the output to the pipe
            close(pipefd[0]);  // Close the read end of the pipe
            run_execve(args);
            exit(EXIT_SUCCESS);
        } else {
            // Parent process
            wait(NULL);  // Wait for child process to finish
            close(pipefd[1]);  // Close the write end of the pipe
            fd_in = pipefd[0];  // Save the input for the next command
            temp = temp->next;  // Move to next command
        }
    }

    return status;
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