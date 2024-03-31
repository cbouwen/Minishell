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

bool	check_cat_no_args(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (temp->type == CMD && ft_strcmp(temp->str, "cat") == 0)
	{
		if (temp->next && temp->next->type == PIPE
			&& temp->next->next->type == CMD)
			return (true);
	}
	return (false);
}

