/*header pls*/

#include "../../../inc/minishell.h"

extern t_signal	g_signal;

int	free_rd(t_rd_collection *rd)
{
	t_rd_collection	*temp_rd;

	temp_rd = rd;
	if (temp_rd->input != NULL)
		free_array(temp_rd->input);
	if (temp_rd->output != NULL)
		free_array(temp_rd->output);
	temp_rd->coll_exists = false;
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

int	rd_error_handler(int err_no, char *str, t_rd_collection *rd)
{
	if (g_signal.in_heredoc == true)
		g_signal.in_heredoc = false;
	if (err_no == 12)
		ft_error("malloc failed\n", 12);
	else if (err_no == 0)
		ft_error(NULL, 0);
	else if (err_no == 2)
	{
		printf("bash: %s", str);
		ft_error(": No such file or directory\n", 1);
	}
	if (rd && err_no != 0)
		free_rd(rd);
	return (ft_error(NULL, err_no));
}
