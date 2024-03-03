/*header pls*/

#include "../../inc/minishell.h"

void	echo(t_token *tokens)
{
	t_token	*temp;
	int		n_flag;

	temp = tokens;
	n_flag = 0;
	if (temp->type == ARG && ft_strcmp(temp->str, "-n") == 0)
	{
		n_flag = 1;
		temp = temp->next;
	}
	while (temp)
	{
		if (temp->type == ARG)
			ft_putstr_fd(temp->str, temp->output);
		temp = temp->next;
	}
	if (n_flag == 0)
			ft_putchar_fd('\n', temp->output);
}