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
	return (0);
}

int	init_rd(t_token *tokens, t_rd_collection *rd)
{
	t_token			*temp;
	t_rd_collection	*temp_rd;

	temp = tokens;
	temp_rd = rd;
	temp_rd->input = ft_calloc(sizeof(char *), count_rd(temp) + 1);
	if (!temp_rd->input)
		return (12);
	temp_rd->output = ft_calloc(sizeof(char *), count_rd(temp) + 1);
	if (!temp_rd->output)
		return (12);
	temp_rd->append = ft_calloc(sizeof(char *), count_rd(temp) + 1);
	if (!temp_rd->append)
		return (12);
	return (0);
}

int	free_rd(t_rd_collection *rd)
{
	t_rd_collection	*temp_rd;

	temp_rd = rd;
	while (temp_rd->input)
	{
		free(temp_rd->input);
		temp_rd->input++;
	}
	free(temp_rd->input);
	while (temp_rd->output)
	{
		free(temp_rd->output);
		temp_rd->output++;
	}
	free(temp_rd->output);
	while (temp_rd->append)
	{
		free(temp_rd->append);
		temp_rd->append++;
	}
	free(temp_rd->append);
	return (0);
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
	for (int i = 0; i < 10; i++)
	{
		if (rd.append[i] != NULL)
			printf("append[%d]: %s\n", i, rd.append[i]);
		else
			break;
	}
	free_rd(&rd);
	return (status);
}