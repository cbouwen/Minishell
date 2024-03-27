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

int fill_rd(t_token *tokens, t_rd_collection *rd)
{
	t_token	*temp;
	t_rd_collection	*temp_rd;
	int i;

	temp = tokens;
	temp_rd = rd;
	i = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIRECT)
		{
			printf("i: %d\n", i);
			if (ft_strcmp(temp->str, "<") == 0 || ft_strcmp(temp->str, ">>") == 0)
				fill_input(temp, temp_rd, i);
			/*else if (ft_strcmp(temp->str, ">") == 0)
				fill_output(temp, temp_redirect);
			else if (ft_strcmp(temp->str, ">>") == 0)
				fill_append(temp, temp_redirect);*/
			i++;
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

	temp = tokens;
	temp_rd = rd;
	if (temp->type == REDIRECT)
	{
		if (ft_strcmp(temp->str, "<") == 0)
			temp_rd->input[i] = ft_strdup(temp->next->str);
		else if (ft_strcmp(temp->str, "<<") == 0)
		{
			input = ft_strdup("h-");
			input = strjoin_free(input, temp->next->str, 0);
			temp_rd->input[i] = input;
		}
	}
	return (0);
}