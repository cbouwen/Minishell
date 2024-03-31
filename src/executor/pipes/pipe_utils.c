/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:25:13 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/31 23:57:36 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	move_to_next(t_token **tokens)
{
	t_token	*temp;

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

int	pipe_error_handler(int err_no)
{
	if (err_no == 1)
		return (ft_error("dup2 failed\n", 2));
	if (err_no == 3)
		return (ft_error("fork failed\n", 3));
	return (ft_error(NULL, err_no));
}
