/*header pls*/

#include "../../inc/minishell.h"

int	run_redirects(t_token *tokens, t_environment *env, t_args *args)
{
	t_token			*temp;
	t_environment	*temp_env;
	int				status;

	temp = tokens;
	temp_env = env;
	status = 0;
	determine_redirect(temp, args);
	determine_file(temp, args);
	printf("redirect: %d\n", args->redirect);
	printf("file: %s\n", args->file);
	return (status);
}
