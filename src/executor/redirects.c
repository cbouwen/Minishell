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
	(void)temp_env;
	status = 0;
	status = determine_redirect(temp, temp_args);
	status = determine_file(temp, temp_args);
	printf("redirect: %d\n", temp_args->redirect);
	printf("file: %s\n", temp_args->file);
	printf("file_exists: %d\n", temp_args->file_exists);
	printf("fd: %d\n", temp_args->fd);
	printf("delimiter: %s\n", temp_args->delimiter);
	return (ft_error(NULL, status));
}
