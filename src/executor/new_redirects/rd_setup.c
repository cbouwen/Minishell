/*header pls*/

#include "../../../inc/minishell.h"

int	redirect_syntax_check(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIRECT)
		{
			if (temp->next->type == ARG)
			{
				if (ft_isdigit(temp->next->str[0]) == 1)
					return (ft_error("syntax error\n", 3));
			}
		}
		temp = temp->next;
	}
	return (rd_error_handler(0, NULL, NULL));
}

int	init_rd(t_token *tokens, t_rd_collection *rd)
{
	t_token			*temp;
	t_rd_collection	*temp_rd;

	temp = tokens;
	temp_rd = rd;
	temp_rd->input = ft_calloc(sizeof(char *), count_rd(temp) + 1);
	if (!temp_rd->input)
		return (rd_error_handler(12, NULL, rd));
	temp_rd->output = ft_calloc(sizeof(char *), count_rd(temp) + 1);
	if (!temp_rd->output)
		return (rd_error_handler(12, NULL, rd));
	temp_rd->input_size = 0;
	temp_rd->output_size = 0;
	temp_rd->i_fd = 0;
	temp_rd->o_fd = 0;
	temp_rd->file_exists = 0;
	temp_rd->coll_exists = true;
	return (rd_error_handler(0, NULL, rd));
}

int redirect_test(t_token *tokens)
{
	t_rd_collection	rd;

	int status = redirect_syntax_check(tokens);
	init_rd(tokens, &rd);
	fill_rd(tokens, &rd);
	for (int i = 0; i < 10; i++)
	{
		if (rd.input[i] != NULL)
			printf("input[%d]: %s\n", i, rd.input[i]);
		else
			break;
	}
	for (int i = 0; i < 10; i++)
	{
		if (rd.output[i] != NULL)
			printf("output[%d]: %s\n", i, rd.output[i]);
		else
			break;
	}
	printf("input_size: %d\n", rd.input_size);
	printf("output_size: %d\n", rd.output_size);
	open_output(&rd);
	if (rd.coll_exists == true)
		free_rd(&rd);
	return (status);
}
