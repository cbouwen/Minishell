/*header pls*/

#include "../../../inc/minishell.h"

int	determine_echo(t_token *tokens)
{
	t_token	*temp;
	int		status;

	temp = tokens;
	status = 0;
	if (temp->next && temp->next->type == ARG)
	{
		status = echo(temp->right);
		return (status);
	}
	else
	{
		status = echo_no_arg(temp);
		return (status);
	}
	return (1);
}

int	echo(t_token *tokens)
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
	while (temp && temp->type == ARG)
	{
		printf("%s", temp->str);
		//ft_putstr_fd(temp->str, output_fd);
		if (temp->has_space)
			//ft_putchar_fd(' ', output_fd);
			printf(" ");
		temp = temp->next;
	}
	if (n_flag == 0)
		printf("\n");
		//ft_putchar_fd('\n', output_fd);
	return (ft_error(NULL, 0));
}

int	echo_no_arg(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	(void)temp;
	printf("\n");
	//ft_putchar_fd('\n', temp->output);
	return (ft_error(NULL, 0));
}
