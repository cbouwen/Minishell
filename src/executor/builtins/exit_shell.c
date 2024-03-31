#include "../../../inc/minishell.h"

int	exit_shell(t_token *tokens, t_env *env, t_args *args)
{
	if (args)
		free_args(args);
	if (tokens)
		free_tokens(tokens);
	if (env)
		free_env(env);
	rl_clear_history();
	exit(0);
}