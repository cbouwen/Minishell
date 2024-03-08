/*header pls*/

#include "../../inc/minishell.h"

void	echo(t_token *tokens)
{
	t_token	*temp;
	int		n_flag;
	int		output_fd;

	temp = tokens;
	n_flag = 0;
	output_fd = temp->output;
	if (temp->type == ARG && ft_strcmp(temp->str, "-n") == 0)
	{
		n_flag = 1;
		temp = temp->next;
	}
	while (temp)
	{
		if (temp->type == ARG)
		{
			output_fd = temp->output;
			ft_putstr_fd(temp->str, output_fd);
			if (temp->has_space == true)
				ft_putchar_fd(' ', output_fd);
		}
		temp = temp->next;
	}
	if (n_flag == 0)
		ft_putchar_fd('\n', output_fd);
}

void	echo_no_arg(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	ft_putchar_fd('\n', temp->output);
}
