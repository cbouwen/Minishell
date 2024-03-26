/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_converter_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:07:42 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/25 18:53:31 by matisse          ###   ########.fr       */
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
	size_t			i;

	temp = env;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

int	init_args(t_args *args)
{
	args->arg_array = NULL;
	args->env_array = NULL;
	args->redirect = TEMP;
	args->heredoc = 0;
	args->heredoc_file = NULL;
	args->file = NULL;
	args->file_exists = 0;
	args->fd = 0;
	args->heredoc_fd = -1;
	args->delimiter = NULL;
	return (0);
}

char	*strjoin_free(char *s1, char *s2, int free_str)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	if (free_str == 1)
		free(tmp);
	return (s1);
}

int	free_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
	}
	free(array);
	return (0);
}
