/*header pls*/

#include "../../inc/minishell.h"

int	run_redirects(t_token *tokens, t_environment *env, t_args *args)
{
	t_token			*temp;
	t_environment	*temp_env;
	t_args			*temp_args;
	int				status;
	//pid_t			pid;

	temp = tokens;
	temp_env = env;
	temp_args = args;
	status = 0;
	status = determine_redirect(temp, temp_args);
	status = determine_file(temp, temp_args);
	/*pid = fork();
	if (pid < 0)
		return (ft_error("redirect: fork error\n", 1));
	else if (pid == 0)
	{
		if (temp_args->redirect == INPUT)
		status = redirect_input(temp, temp_env, temp_args);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}*/

	if (temp_args->redirect == INPUT)
		status = redirect_input(temp, temp_env, temp_args);
	
	/*else if (temp_args->redirect == APPEND)
		status = redirect_append(temp_args);
	else if (temp_args->redirect == INPUT)
		status = redirect_input(temp_args);
	else if (temp_args->heredoc == 1)
		status = heredoc(temp_args);*/

	printf("redirect: %d\n", temp_args->redirect);
	printf("file: %s\n", temp_args->file);
	printf("file_exists: %d\n", temp_args->file_exists);
	printf("fd: %d\n", temp_args->fd);
	printf("delimiter: %s\n", temp_args->delimiter);
	return (ft_error(NULL, status));
}

int redirect_input(t_token *tokens, t_environment *env, t_args *args)
{
	t_token			*temp;
	t_environment	*temp_env;
	t_args			*temp_args;

	temp = tokens;
	temp_env = env;
	temp_args = args;
	int saved_stdin = dup(STDIN_FILENO);
	if (dup2(temp_args->fd, STDIN_FILENO) == -1)
		return (ft_error("redirect: dup2 error\n", 1));
	close(temp_args->fd);
	int status = prep_cmd(temp, temp_env, temp_args);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	return (ft_error(NULL, status));
}
