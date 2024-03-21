/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_converter_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:07:42 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/21 20:53:36 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	count_tokens(t_token *tokens)
{
	t_token	*temp;
	int		i;

	temp = tokens;
	i = 0;
	while (temp && temp->type != PIPE && temp->type != REDIRECT)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

size_t	count_env(t_environment *env)
{
	t_environment	*temp;
	size_t				i;

	temp = env;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

int init_args(t_args *args)
{
	args->arg_array = NULL;
	args->env_array = NULL;
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2, bool free_str)
{
	char *tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	if (free_str == true)
		free(tmp);
	return (s1);
}

int	free_args(t_args *args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args->arg_array[i])
		{
			free(args->arg_array[i]);
			i++;
		}
		i = 0;
		while (args->env_array[i])
		{
			free(args->env_array[i]);
			i++;
		}
		free(args->arg_array);
		free(args->env_array);
		free(args);
	}
	return (0);
}
