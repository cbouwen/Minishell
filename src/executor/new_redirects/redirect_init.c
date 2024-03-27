/*header pls*/

#include "../../../inc/minishell.h"

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

int fill_rd(t_token *tokens, t_rd_collection *rd)
{
	t_token	*temp;
	t_rd_collection	*temp_rd;
	int i;
	int j;
	int k;

	temp = tokens;
	temp_rd = rd;
	i = -1;
	j = -1;
	k = -1;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIRECT)
		{
			if (ft_strcmp(temp->str, "<") == 0 || ft_strcmp(temp->str, "<<") == 0)
				fill_input(temp, temp_rd, ++i);
			else if (ft_strcmp(temp->str, ">") == 0)
				fill_out_app(temp, temp_rd, ++j, ">");
			else if (ft_strcmp(temp->str, ">>") == 0)
				fill_out_app(temp, temp_rd, ++k, ">>");
		}
		temp = temp->next;
	}
	return (0);
}

int fill_input(t_token *tokens, t_rd_collection *rd, int i)
{
	t_token			*temp;
	t_rd_collection	*temp_rd;
	char			*input;
	char			*temp_input;

	temp = tokens;
	temp_rd = rd;
	input = NULL;
	temp_input = NULL;
	if (temp->type == REDIRECT)
	{
		if (ft_strcmp(temp->str, "<") == 0)
		{
			temp_rd->input[i] = ft_strdup(temp->next->str);
			if (!temp_rd->input[i])
				return (12);
		}
		else if (ft_strcmp(temp->str, "<<") == 0)
		{
			input = ft_strdup("h_");
			if (!input)
				return (12);
			temp_input = strjoin_free(input, temp->next->str, 0);
			if (!temp_input)
			{
				free(input);
				return (12);
			}
			free(input);
			input = temp_input;
			temp_rd->input[i] = input;
		}
	}
	return (0);
}

int fill_out_app(t_token *tokens, t_rd_collection *rd, int i, char *rd_type)
{
	t_token         *temp;
	t_rd_collection *temp_rd;
	char			**target;

	temp = tokens;
	temp_rd = rd;
	if (temp->type == REDIRECT)
	{
		if (ft_strcmp(temp->str, rd_type) == 0)
		{
			if (ft_strcmp(rd_type, ">") == 0)
				target = &(temp_rd->output[i]);
			else if (ft_strcmp(rd_type, ">>") == 0)
				target = &(temp_rd->append[i]);
			else
				return (0);
			*target = ft_strdup(temp->next->str);
			if (!*target)
				return (12);
		}
	}
	return (0);
}