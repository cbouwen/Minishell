/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:28:48 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/05 16:30:24 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int find_quote(t_token *token, char c)
{
    if (token->str[0] == c)
        return (0);
    return (1);
}

int count_quotes(char *str)
{
    int i;
    int quotes;

    i = 0;
    quotes = 0;
    while (str[i])
    {
        if (str[i] == 39)
            quotes++;
        i++;
    }
    return (quotes);
}

