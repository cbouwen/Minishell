/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:50:48 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/25 18:40:47 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	export_var(t_token *tokens, t_environment *env)
{
	char	*var_name;
	char	*var_value;
	int		status;

	var_name = NULL;
	var_value = NULL;
	status = 0;
	if (count_tokens(tokens) == 2)
		status = special_export(tokens->next->str, &var_name, &var_value);
	else
	{
		status = extract_name(tokens->next->str, &var_name);
		status = extract_value(tokens->next->next->str, &var_value);
	}
	printf("var_name: %s\n", var_name);
	if (status != 0)
		return (ft_error(NULL, status));
	if (check_env_val_exists(env, var_name) == 0)
		status = update_env_val(env, var_name, var_value, false);
	else
		status = add_env_val(env, var_name, var_value);
	if (var_name)
		free(var_name);
	if (var_value)
		free(var_value);
	return (ft_error(NULL, status));
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
			return (ft_error(NULL, 0));
		}
		else
			env = env->next;
	}
	return (ft_error("export: unexpected error\n", 1));
}

int	add_env_val(t_environment *env, char *var_name, char *var_value)
{
	t_environment	*new;

	new = create_node(var_name, var_value);
	ft_lstadd_back_ms(&env, new);
	return (ft_error(NULL, 0));
}
