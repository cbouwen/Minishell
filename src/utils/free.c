#include "../../inc/minishell.h"

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->str)
		free(token->str);
	free(token);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free_token(token);
		token = tmp;
	}
}
