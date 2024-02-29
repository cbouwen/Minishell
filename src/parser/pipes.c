/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:39:17 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/29 13:15:34 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    parse_pipes(t_token *token) //does nothing if pipe = 1 ?
{
    t_token    *tmp;

    tmp = NULL;
    while (token)
    {
        if (token->type == PIPE)
        {
            if (tmp)
            {
                token->left = tmp;
                tmp->parent = token;
            }
            tmp = token;
        }
		if (token->next == NULL)
			break;
        token = token->next;
    }
	reset_list(&token);
}
