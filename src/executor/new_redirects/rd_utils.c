/*header pls*/

#include "../../../inc/minishell.h"

int	free_rd(t_rd_collection *rd)
{
	t_rd_collection	*temp_rd;

	temp_rd = rd;
	free_array(temp_rd->input);
	free_array(temp_rd->output);
	return (0);
}

size_t count_rd(t_token *tokens)
{
	t_token	*temp;
	size_t	count;

	temp = tokens;
	count = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIRECT)
			count++;
		temp = temp->next;
	}
	return (count);
}

int	rd_error_handler(int err_no)
{
	if (err_no == 12)
		ft_error("malloc failed\n", 12);
	return (err_no);
}
