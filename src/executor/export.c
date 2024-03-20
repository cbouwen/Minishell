/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:50:48 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/20 18:11:07 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export_var(t_token *tokens, t_environment *env)
{
	t_token			*temp;
	t_environment	*temp_env;
	char			*var_name;
	char			*var_value;

	temp = tokens;
	temp_env = env;
	var_name = NULL;
	var_value = NULL;
	extract_name(temp->str, &var_name);
	extract_value(temp->next->str, &var_value);
	if (check_env_val_exists(temp_env, var_name) == 0)
		update_env_val(temp_env, var_name, var_value, false);
	else
		add_env_val(temp_env, var_name, var_value);
	free(var_name);
	free(var_value);
	return (0);	
}

int	update_env_val(t_environment *env, char *var_name, char *var_value, bool cd)
{
	if (cd && check_env_val_exists(env, var_name) == 1)
		add_env_val(env, var_name, "temp");
	while (env)
	{
		if (ft_strcmp(var_name, env->name) == 0)
		{
			free(env->value);
			env->value = ft_strdup(var_value);
			return (0);
		}
		else
			env = env->next;
	}
	return (1);
}

int	add_env_val(t_environment *env, char *var_name, char *var_value)
{
	t_environment *new;

	new = create_node(var_name, var_value);
	ft_lstadd_back_ms(&env, new);
	return (0);
}
