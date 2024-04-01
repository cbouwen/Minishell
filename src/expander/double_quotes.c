/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:22:35 by cbouwen           #+#    #+#             */
/*   Updated: 2024/04/01 12:23:21 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_env(char *str, t_env *env)
{
	t_env	*tmp;
	char	*substr;

	tmp = env;
	if (!(ft_strcmp(str, "$?")))
	{
		free(str);
		return (ft_itoa(g_signal.err_no));
	}
	while (tmp)
	{
		if (ft_strcmp((str + 1), tmp->name) == 0)
		{
			substr = ft_strdup(tmp->value);
			if (!substr)
				break ;
			free(str);
			return (substr);
		}
		tmp = tmp->next;
	}
	free(str);
	return (ft_strdup(""));
}

char	*find_new_str(char *str, t_env *env, int *i)
{
	int		j;
	char	*s1;
	char	*s2;
	char	*s3;

	j = *i + 1;
	while (str[j] && str[j] != '$' && str[j] != ' ' && str[j] != '"'
		&& str[j] != 39)
		j++;
	s2 = ft_strndup(str + *i, j - *i);
	s2 = find_env(s2, env);
	if (!s2)
		return (NULL);
	s1 = ft_strndup(str, *i);
	*i = ft_strlen(s2);
	s3 = ft_strjoin_quotes(s1, s2);
	s1 = ft_strdup(str + j);
	s2 = ft_strjoin_quotes(s3, s1);
	free(str);
	return (s2);
}

int	expand_double_quote(t_token **tokens, t_env *env)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = ft_strdup((*tokens)->str);
	while (newstr[i])
	{
		if (newstr[i] == '$')
		{
			newstr = find_new_str(newstr, env, &i);
			if (!newstr)
				return (0);
		}
		i++;
	}
	if (newstr)
	{
		free((*tokens)->str);
		(*tokens)->str = ft_strdup(newstr);
		free(newstr);
	}
	return (1);
}
