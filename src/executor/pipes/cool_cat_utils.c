/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cool_cat_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:55:16 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/31 23:55:57 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

bool	check_cat(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (temp->type == CMD && ft_strcmp(temp->str, "cat") == 0)
	{
		if (temp->next->type == PIPE)
			return (true);
	}
	return (false);
}

bool	check_cat_no_args(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (temp->type == CMD && ft_strcmp(temp->str, "cat") == 0)
	{
		if (temp->next && temp->next->type == PIPE
			&& temp->next->next->type == CMD)
			return (true);
	}
	return (false);
}
