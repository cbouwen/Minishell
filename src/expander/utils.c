/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:28:48 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/06 16:09:34 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t   counter(char const *s) 
{
    size_t  i;  

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char    *ft_strjoin_quotes(char *s1, char *s2)
{
    char    *s3;
    size_t  slen1;
    size_t  slen2;
    size_t  i;  
    size_t  j;  

    i = -1; 
    j = -1; 
    slen1 = counter(s1);
    slen2 = counter(s2);
    s3 = (char *)malloc((slen1 + slen2 + 1) * sizeof(char));
    if (!s3)
        return (NULL);
    while (s1[++i])
        s3[i] = s1[i];
    while (s2[++j])
        s3[i + j] = s2[j];
    s3[slen1 + slen2] = '\0';
	free(s1);
	free(s2);
    return (s3);
}

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

