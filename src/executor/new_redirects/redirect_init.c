/*header pls*/

#include "../../../inc/minishell.h"

int fill_redirect(t_token *tokens, t_redirect *redirect)
{
	t_token	*temp;
	t_redirect	*temp_redirect;

	temp = tokens;
	temp_redirect = redirect;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIRECT)
		{
			if (ft_strcmp(temp->str, "<") == 0 || ft_strcmp(temp->str, ">>") == 0)
				fill_input(temp, temp_redirect);
			/*else if (ft_strcmp(temp->str, ">") == 0)
				fill_output(temp, temp_redirect);
			else if (ft_strcmp(temp->str, ">>") == 0)
				fill_append(temp, temp_redirect);*/
		}
		temp = temp->next;
	}
	return (0);
}

int fill_input(t_token *temp, t_rd_collection *rd)
{
	t_token			*temp;
	t_rd_collection	*temp_rd;
	char			*input;

	temp = tokens;
	temp_rd = rd;
	if (temp->type == REDIRECT)
	{
		if (ft_strcmp(temp->str, "<") == 0)
		{
			temp_rd->input = ft_strdup(temp->next->str);
			temp_rd->input_type = 1;
		}
		else if (ft_strcmp(temp->str, "<<") == 0)
		{
			input = ft_strdup("h-");
			input = strjoin_free(input, temp->next->str, 0);
			temp_rd->input = input;
		}
	}
}