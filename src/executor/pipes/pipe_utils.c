/*header pls*/

#include "../../../inc/minishell.h"

int move_to_next(t_token **tokens)
{
	t_token *temp;

	temp = *tokens;
	while (temp && temp->type != PIPE)
		temp = temp->next;
	if (temp)
		*tokens = temp->next;
	return (0);
}

void	print_args(t_args *args, t_token **tokens)
{
	int i;

	i = 0;
	fill_args(args, *tokens);
	while (args->args[i])
	{
		printf("args[%d]: %s\n", i, args->args[i]);
		i++;
	}
	move_to_next(tokens);
	i = 0;
	while (args->env[i])
	{
		printf("env[%d]: %s\n", i, args->env[i]);
		i++;
	}
	return ;
}