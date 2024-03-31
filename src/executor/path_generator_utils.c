/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_generator_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:40:15 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/28 17:55:13 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_absolute_path(char *path)
{
	char		temp;
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (-1);
	temp = path[0];
	if (temp == '/' && access(path, X_OK) == 0 && S_ISREG(path_stat.st_mode))
		return (1);
	else if (temp == '/' && S_ISREG(path_stat.st_mode) == false)
		return (-1);
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
	return (-2);
}

int	split_path(t_args *args, char ***exec_path)
{
	int		i;
	char	*path;
	char	*path_start;

	i = find_path(args);
	if (i == -2)
		return (-2);
	path = args->env_array[i];
	path_start = ft_strchr(path, '=');
	if (!path_start)
		return (3);
	path_start++;
	*exec_path = ft_split(path_start, ':');
	if (!*exec_path)
		return (3);
	i = 0;
	return (0);
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
		return (12);
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

int	path_error_handler(int err_no)
{
	if (err_no == 12)
		return (ft_error("execve: malloc error\n", 12));
	else if (err_no == 1)
		return (ft_error("execve: no executable file or directory\n", 12));
	else if (err_no == -1)
		return (ft_error("execve: no executable file or directory\n", 1));
	else if (err_no == -2)
		return (ft_error("execve: no PATH variable set\n", 1));
	else if (err_no == 3)
		return (ft_error("execve: split_path error\n", 1));
	else if (err_no == 4)
		return (ft_error("command not found\n", 127));
	return (err_no);
}
