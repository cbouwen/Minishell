/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:50:48 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/05 17:19:40 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export_var(t_token *tokens, t_environment *env)
{
	t_token			*temp;
	t_environment	*temp_env;
	char			*var_name;

	temp = tokens;
	temp_env = env;
	var_name = NULL;
	if (check_env_val_exists(temp, temp_env, &var_name) == 1)
		printf("%s\n", var_name);
	free(var_name);
	return (0);	
}

int	check_env_val_exists(t_token *tokens, t_environment *env, char **var_name)
{
	int		sign_loc;
	char	*value;

	sign_loc = 0;
	value = NULL;
	if (tokens->type == ARG)
	{
		value = ft_strchr(tokens->str, '=');
		if (!value)
			return (2);
	}
	else
		return (2);
	sign_loc = value - tokens->str;
	*var_name = ft_substr(tokens->str, 0, sign_loc);
	while (env)
	{
		if (ft_strcmp(*var_name, env->name) == 0)
			return (1);
		else
			env = env->next;
	}
	return (0);
}
