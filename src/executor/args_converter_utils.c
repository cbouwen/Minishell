/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_converter_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:07:42 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/29 19:24:23 by mlegendr         ###   ########.fr       */
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

size_t	count_env(t_env *env)
{
	t_env	*temp;
	size_t	i;

	temp = env;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

int	init_args(t_args *args, t_token *tokens, t_env *env)
{
	args->arg_array = NULL;
	args->env_array = NULL;
	args->fd[0] = -1;
	args->fd[1] = -1;
	args->in_fd = -1;
	args->pipe_count = -1;
	args->a_stdin = 0;
	args->a_stdout = 0;
	args->tokens = tokens;
	args->env = env;
	return (0);
}

char	*strjoin_free(char *s1, char *s2, int free_str)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(tmp, s2);
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
		free(array);
		array = NULL;
	}
	return (0);
}
