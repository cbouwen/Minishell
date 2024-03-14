/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:32:35 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/14 19:14:34 by mlegendr         ###   ########.fr       */
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

