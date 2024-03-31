/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:41:17 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/31 23:59:30 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	extract_name(char *token_str, char **var_name)
{
	int		sign_loc;
	char	*value;

	sign_loc = 0;
	value = NULL;
	value = ft_strchr(token_str, '=');
	sign_loc = value - token_str;
	*var_name = ft_substr(token_str, 0, sign_loc);
	if (!*var_name)
		return (ft_error("export: malloc error\n", 12));
	return (ft_error(NULL, 0));
}

int	extract_value(char *token_str, char **var_value)
{
	*var_value = ft_strdup(token_str);
	if (!*var_value)
		return (ft_error("export: malloc error\n", 12));
	return (ft_error(NULL, 0));
}

int	check_env_val_exists(t_env *env, char *var_name)
{
	while (env)
	{
		if (ft_strcmp(var_name, env->name) == 0)
			return (0);
		else
			env = env->next;
	}
	return (1);
}

int	special_export(char *token_str, char **var_name, char **var_value)
{
	int	status;
	int	sign_loc;

	(void)var_value;
	status = 0;
	sign_loc = 0;
	status = extract_name(token_str, var_name);
	if (status != 0)
		return (ft_error(NULL, status));
	sign_loc = ft_strchr(token_str, '=') - token_str;
	*var_value = ft_strdup(token_str + sign_loc + 1);
	return (ft_error(NULL, 0));
}
