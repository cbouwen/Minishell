/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:12 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/27 13:04:51 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*void    place_pipes(t_token *tmp, int pipes)
{
    while (tmp)
    {
        if (tmp->)
    }
}

void    parse_tree(t_token *tmp, t_token *first_token)
{
    int pipes;

    pipes = count_pipes(*tmp);
    tmp = first_token;
    if (pipes != 0)
        place_pipes(tmp, pipes);

}
*/

int     count_pipes(t_token tmp)
{
    int pipes;

    pipes = 0;
    while (tmp)
    {
        if (tmp.type == PIPE)
            pipes++;
        tmp = tmp->next;
    }
    return (pipes)
}

int parser(t_token **tokens, t_token **head)
{
   t_token      *tmp;
   t_token      *first_token;
   int          pipes;

    pipes = pipe_counter(tmp);
    first_token = *tokens;
    tmp = *tokens;
    parse_pipes(tmp, head);
    tmp = first_token;
    parse_redirects(tmp, head, pipes);
    tmp = first_token;
    parse_commands(tmp, head);
    tmp = first_token;
    parse_arguments(tmp, head);
    tmp = first_token;
    return (1);
}
