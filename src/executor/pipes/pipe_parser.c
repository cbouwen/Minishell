/*header pls*/

#include "../../../inc/minishell.h"

/*int	pipe_decider(t_token **tokens, t_env *env, t_args *args)
{
	t_env	*temp_env;
	t_args	*temp_args;
	int		status;

	status = 0;
	temp_env = env;
	temp_args = args;
	if (count_consecutive_cats(*tokens))
		printf("special case\n");
	else
		status = run_piped_cmd(&tokens, temp_env, temp_args);
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
	while (pipe_count > 0)
	{
		if (pipe_count == 1)
			status = run_last_pipe(&temp, temp_env, temp_args);
		else
			status = run_pipe(&temp, temp_env, temp_args);
		if (status != 0)
			return (status);
		pipe_count--;
	}
	
}*/