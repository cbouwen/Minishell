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
	printf("cat count: %d\n", count_cats(*tokens));
	return (status);
}

int	count_cats(t_token *tokens)
{
	t_token	*temp;
	int		count;

	count = 0;
	temp = tokens;
	while (temp)
	{
		if (temp->type == CMD && ft_strcmp(temp->str, "cat") == 0)
		{
			if (!temp->next || temp->next->type != PIPE)
				break ;
			else if (temp->next->type == PIPE && temp->next->next->type == CMD)
			{
				if (ft_strcmp(temp->next->next->str, "cat") == 0)
					count++;
			}
		}
		temp = temp->next;
	}
	return (count);
}
