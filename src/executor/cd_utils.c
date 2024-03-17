/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:32:35 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/15 19:03:57 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int get_env_val(t_environment *env, char *var_name, char **var_value)
{	
	if (check_env_val_exists(env, var_name) == 1)
		return (1);
	while (env)
	{
		if (ft_strcmp(var_name, env->name) == 0)
		{
			*var_value = ft_strdup(env->value);
			return (0);
		}
		else
			env = env->next;
	}
	return (1);
}

int	update_pwd(t_environment *env, char *path)
{
	char	*current_pwd;
	
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (1);
	update_env_val(env, "OLDPWD", path, true);
	update_env_val(env, "PWD", current_pwd, true);
	free(current_pwd);
	return (0);
}

int	free_and_return(char *str1, char *str2, int errno)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (ft_error(NULL));
}
