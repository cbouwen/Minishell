/*header pls*/

#include "../../../inc/minishell.h"

int	cool_cat(t_token **tokens, t_env *env, t_args *args)
{
	t_token	*temp;
	t_env	*temp_env;
	t_args	*temp_args;
	int		status;

	status = 0;
	temp = *tokens;
	temp_env = env;
	temp_args = args;
	(void)temp;
	(void)temp_env;
	(void)temp_args;
	printf("cat count: %d\n", check_cat(*tokens));
	return (status);
}
