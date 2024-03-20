/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:08:54 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/20 18:11:40 by mlegendr         ###   ########.fr       */
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

int	execve_executor(t_token *tokens)
{
	t_args	*args;
	int		status;

	args = malloc(sizeof(t_args));
	status = fill_args(args, tokens);
	if (status != 0)
	{
		free_args(args);
		return (status);
	}
	status = run_execve(args);
	free_args(args);
	return (status);
}

int	fill_args(t_args *args, t_token *tokens)
{
	t_token	*temp;
	size_t	i;
	size_t	count;

	temp = tokens;
	args->arg_array = malloc(sizeof(char *) * (count_tokens(temp) + 1));
	if (!args->arg_array)
		return (12);
	i = 0;
	temp = tokens;
	count = count_tokens(temp);
	while (temp && i < count)
	{
		args->arg_array[i] = ft_strdup(temp->str);
		if (!args->arg_array[i])
			return (12);
		i++;
		temp = temp->next;
	}
	args->arg_array[i] = NULL;
	return (0);
}

int	run_execve(t_args *args)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(args->arg_array[0], args->arg_array, NULL) == -1)
		if (execve(args->arg_array[0], args->arg_array, NULL) == -1)
			exit(1);
	}
	else
		waitpid(pid, &status, 0);
	return (status);
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
		free(args->arg_array);
		free(args);
	}
	return (0);
}
