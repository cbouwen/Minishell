/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_converter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:00:59 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/29 18:49:44 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	fill_args(t_args *args, t_token *tokens)
{
	t_token	*temp;
	size_t	i;
	size_t	count;

	temp = tokens;
	args->arg_array = malloc(sizeof(char *) * (count_tokens(temp) + 1));
	if (!args->arg_array)
		return (ft_error("fill_args: malloc error\n", 12));
	i = 0;
	temp = tokens;
	count = count_tokens(temp);
	while (temp && i < count)
	{
		args->arg_array[i] = ft_strdup(temp->str);
		if (!args->arg_array[i])
			return (ft_error("fill_args: malloc error\n", 12));
		i++;
		temp = temp->next;
	}
	args->arg_array[i] = NULL;
	return (ft_error(NULL, 0));
}

int	fill_env(t_args *args, t_env *env)
{
	t_env	*temp;
	size_t	i;
	size_t	count;
	char	*tmp;

	temp = env;
	args->env_array = malloc(sizeof(char *) * (count_env(temp) + 1));
	if (!args->env_array)
		return (ft_error("fill_env: malloc error\n", 12));
	i = 0;
	temp = env;
	count = count_env(temp);
	while (temp && i < count)
	{
		tmp = ft_strjoin(temp->name, "=");
		if (!tmp)
			return (ft_error("fill_env: malloc error\n", 12));
		args->env_array[i] = strjoin_free(tmp, temp->value, 1);
		if (!args->env_array[i])
			return (ft_error("fill_env: malloc error\n", 12));
		i++;
		temp = temp->next;
	}
	args->env_array[i] = NULL;
	return (ft_error(NULL, 0));
}

int	free_args(t_args *args)
{
	if (args->arg_array)
		free_array(args->arg_array);
	if (args->env_array)
		free_array(args->env_array);
	return (0);
}

int	free_args_full(t_args *args, int err_no)
{
	if (args->arg_array)
		free_array(args->arg_array);
	if (args->env_array)
		free_array(args->env_array);
	free_tokens(args->tokens);
	free_env(args->env);
	return (err_no);
}

void	printf_args_env(t_args *args)
{
	int	i;

	i = 0;
	while (args->arg_array[i])
	{
		printf("arg_array[%d]: %s\n", i, args->arg_array[i]);
		i++;
	}
	printf("\n-----------------\n\n");
	i = 0;
	while (args->env_array[i])
	{
		printf("env_array[%d]: %s\n", i, args->env_array[i]);
		i++;
	}
}
