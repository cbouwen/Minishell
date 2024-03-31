/*header pls*/

#include "../../../inc/minishell.h"

bool	check_cat(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (temp->type == CMD && ft_strcmp(temp->str, "cat") == 0)
	{
		if (temp->next->type == PIPE)
			return (true);
	}
	return (false);
}

int count_cat(t_token *tokens)
{
	t_token	*temp;
	int		count;

	count = 0;
	temp = tokens;
	while (temp)
	{
		if (temp->type == CMD && ft_strcmp(temp->str, "cat") == 0)
		{
			if (temp->next->type == PIPE && temp->next->next->type == CMD)
			{
				if (ft_strcmp(temp->next->next->str, "cat") == 0)
					count++;
				else
					break ;
			}
		}
		temp = temp->next;
	}
	return (count);
}

