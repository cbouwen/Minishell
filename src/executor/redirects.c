/*header pls*/

#include "../../inc/minishell.h"

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
	status = determine_redirect(temp, temp_args);
	status = determine_file(temp, temp_args);
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
	if (dup2(temp_args->fd, STDIN_FILENO) == -1)
		return (ft_error("redirect: dup2 error\n", 1));
	close(temp_args->fd);
	int status = prep_cmd(temp, temp_env, temp_args);
	return (ft_error(NULL, status));
}
