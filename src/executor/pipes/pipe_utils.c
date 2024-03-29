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

void	print_args(t_token **tokens, t_args *args)
{
	int i;

	i = 0;
	fill_args(args, *tokens);
	while (args->arg_array[i])
	{
		printf("arg_array[%d]: %s\n", i, args->arg_array[i]);
		i++;
	}
	move_to_next(tokens);
	i = 0;
	while (args->arg_array[i])
	{
		printf("arg_array[%d]: %s\n", i, args->arg_array[i]);
		i++;
	}
	return ;
}