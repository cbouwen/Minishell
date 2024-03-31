#include "../../../inc/minishell.h"

int	exit_shell(t_token *tokens, t_env *env, t_args *args)
{
	if (args)
		free_args(args);
	clean_exit(tokens, env, NULL);
	return (0);
}
