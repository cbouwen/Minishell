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

/*int init_redirect(t_token *tokens, t_redirect *redirect)
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
				init_input(temp, temp_redirect);
			else if (ft_strcmp(temp->str, ">") == 0)
				init_output(temp, temp_redirect);
			else if (ft_strcmp(temp->str, ">>") == 0)
				init_append(temp, temp_redirect);
		}
		temp = temp->next;
	}
}*/

int redirect_test(t_token *tokens)
{
	t_rd_collection	rd;

	int status = redirect_syntax_check(tokens);
	init_redirect(tokens, &rd);
	fill_redirect(tokens, &rd);
	for (int i = 0; i < 10; i++)
	{
		if (rd.input[i] != NULL)
			printf("input[%d]: %s\n", i, rd.input[i]);
		else
			break;
	}
	return (status);
}