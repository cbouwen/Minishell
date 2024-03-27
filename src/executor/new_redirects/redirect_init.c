/*header pls*/

#include "../../../inc/minishell.h"

int fill_redirect(t_token *tokens, t_rd_collection *rd)
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
			i++;
			if (ft_strcmp(temp->str, "<") == 0 || ft_strcmp(temp->str, ">>") == 0)
				fill_input(temp, temp_rd, i);
			/*else if (ft_strcmp(temp->str, ">") == 0)
				fill_output(temp, temp_redirect);
			else if (ft_strcmp(temp->str, ">>") == 0)
				fill_append(temp, temp_redirect);*/
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
}