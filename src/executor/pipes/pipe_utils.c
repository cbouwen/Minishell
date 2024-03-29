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

int	count_pipes(t_token *tokens)
{
	t_token	*temp;
	int		count;

	count = 0;
	temp = tokens;
	while (temp)
	{
		if (temp->type == PIPE)
			count++;
		temp = temp->next;
	}
	return (count);
}

bool	count_consecutive_cats(t_token *tokens)
{
	t_token	*temp;
    char	*prev_cmd;

	temp = tokens;
	prev_cmd = NULL;
    while (temp) {
        if (temp->type == CMD) 
		{
            if (prev_cmd && ft_strcmp(prev_cmd, "cat") == 0
				&& ft_strcmp(temp->str, "cat") == 0)
                return (true);
            prev_cmd = temp->str;
        }
        temp = temp->next;
    }
    return false;
}

void	print_args(t_token **tokens, t_args *args)
{
	int i = 0, j = count_pipes(*tokens);
	while (i <= j)
	{
		int k;

		k = 0;
		if (args->arg_array)
			free_array(args->arg_array);
		fill_args(args, *tokens);
		while (args->arg_array[k])
		{
			printf("arg_array[%d]: %s\n", k, args->arg_array[k]);
			k++;
		}
		move_to_next(tokens);
		i++;
	}
	printf("%d\n", count_consecutive_cats(*tokens));
	return ;
}
