/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_generator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:40:15 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/22 20:50:33 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_absolute_path(char *path, t_args *args)
{
	char		temp;
	struct stat	path_stat;

	stat(path, &path_stat);
	temp = path[0];
	args->exec_path = ft_calloc(sizeof(char *), 1);
	if (temp == '/' && access(path, X_OK) == 0 && S_ISREG(path_stat.st_mode))
		return (1);
	else if (temp == '/' && S_ISREG(path_stat.st_mode) == false)
		return (ft_error("execve: not an executable file\n", -1));
	else if (temp == '/')
		return (ft_error("execve: not a relative or absolute path\n", -1));
	return (2);
}

int	find_path(t_args *args)
{
	int	i;

	i = 0;
	while (args->env_array[i])
	{
		if (ft_strncmp(args->env_array[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (ft_error("execve: no PATH variable\n", -1));	
}

int split_path(t_args *args)
{
	int		i;
	char	*path;
	char	*path_start;

	i = find_path(args);
	if (i == -1)
		return (ft_error(NULL, 1));
	path = args->env_array[i];
	path_start = ft_strchr(path, '=');
	if (!path_start)
		return (ft_error("execve: ft_strchr error\n", 1));
	path_start++;
	args->exec_path = ft_split(path_start, ':');
	if (!args->exec_path)
		return (ft_error("execve: split error\n", 1));
	i = 0;
	return (ft_error(NULL, 0));
}

int	assemble_path(t_args *args)
{
	int		i;

	i = -1;
	if (check_absolute_path(args->arg_array[0], args) == -1)
	{
		printf("absolute path\n");
		return (ft_error(NULL, 2));
	}
	if (check_absolute_path(args->arg_array[0], args) == 1)
		return (ft_error(NULL, 0));
	else
	{
		if (split_path(args) == 1)
			return (ft_error(NULL, 1));
		while (args->exec_path[++i])
		{
			if (true_path_ass(args->exec_path[i], args) == 0)
				return (ft_error(NULL, 2));
			else if (true_path_ass(args->exec_path[i], args) == 12)
				return (ft_error(NULL, 1));
		}
		return(ft_error("execve: no executable found\n", 1));
	}
	return (ft_error(NULL, 0));
}

int	true_path_ass(char *path, t_args *args)
{
	char	*test_path;
	char	*command;
	int		j;
	int		len;
	
	j = 0;
	len = 0;
	command = args->arg_array[0];
	j = ft_strlen(path) + ft_strlen(command);
	test_path = malloc(sizeof(char) * j + 2);
	if (!test_path)
		return (ft_error("execve: malloc error", 12));
	len = ft_strlen(path) + 1;
	ft_strlcpy(test_path, path, len);
	ft_strlcat(test_path, "/", len + 1);
	ft_strlcat(test_path, command, j + 4);
	if (access(test_path, X_OK) == 0)
	{
		free(args->arg_array[0]);
		args->arg_array[0] = ft_strdup(test_path);
		free(test_path);
		return (0);
	}
	free(test_path);
	return (1);
}