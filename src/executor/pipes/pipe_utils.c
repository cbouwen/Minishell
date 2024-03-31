/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:25:13 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/29 19:46:46 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

//extern t_signal	g_signal;

int	move_to_next(t_token **tokens)
{
	t_token *temp;

	temp = *tokens;
	while (temp && temp->type != PIPE && temp->next)
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

int	check_cat(t_token *tokens)
{
	t_token	*temp;
	int		count;

	temp = tokens;
	count = 0;
	while (temp)
	{
		if (temp->type == CMD && ft_strcmp(temp->str, "cat") == 0)
		{
			if (!temp->next || temp->next->type != PIPE)
				break ;
			else if (temp->next->type == PIPE && temp->next->next->type == CMD)
			{
				if (ft_strcmp(temp->next->next->str, "cat") == 0)
					count++;
			}
		}
		temp = temp->next;
	}
	return (count);
}

int	pipe_error_handler(int err_no)
{
	if (err_no == 1)
		return (ft_error("dup2 failed\n", 2));
	if (err_no == 3)
		return (ft_error("fork failed\n", 3));
	return (ft_error(NULL, err_no));
}

void	print_args(t_token **tokens, t_args *args)
{
	int j;
	j = count_pipes(*tokens);
	printf("%d\n", check_cat(*tokens));
	while (j >= 0)
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
		j--;
	}
	return ;
}