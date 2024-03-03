/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:42 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/08 17:41:44 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	start(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->type == CMD)
		{
			if (ft_strcmp(temp->str, "echo") == 0)
				echo(temp->right);
		}
		temp = temp->next;
	}
}
