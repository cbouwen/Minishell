/*header pls*/

#include "../../../inc/minishell.h"

int	cool_cat(t_token **tokens, t_env *env, t_args *args)
{
	t_token	*temp;
	t_env	*temp_env;
	t_args	*temp_args;
	int		status;
	int		count;

	status = 0;
	count = 0;
	temp = *tokens;
	temp_env = env;
	temp_args = args;
	(void)temp_env;
	(void)temp_args;
	while (temp)
	{
		if (check_cat_no_args(temp))
		{
			count++;
			move_to_next(tokens);
		}
		temp = temp->next;
	}
	printf("count: %d\n", count);
	return (status);
}
