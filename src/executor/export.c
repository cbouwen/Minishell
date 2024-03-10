/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:50:48 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/08 16:54:11 by mlegendr         ###   ########.fr       */
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
	(void)temp_env;
	var_name = NULL;
	var_value = NULL;
	printf("export_var: tokens->str: %s\n", temp->str);
	extract_name(temp->str, &var_name);
	printf("export_var: tokens->str: %s\n", temp->next->str);
	extract_value(temp->next->str, &var_value);
	printf("var_name: %s\n", var_name);
	printf("var_value: %s\n", var_value);
	/*if (check_env_val_exists(temp_env, var_name) == 1)
		update_env_val(temp_env, var_name, var_value);
	else
		add_env_val(temp_env, var_name, var_value);*/
	free(var_name);
	free(var_value);
	return (0);	
}

int	extract_name(char *token_str, char **var_name)
{
	int		sign_loc;
	char	*value;

	sign_loc = 0;
	value = NULL;
	value = ft_strchr(token_str, '=');
	if (!value)
		return (1);
	sign_loc = value - token_str;
	*var_name = ft_substr(token_str, 0, sign_loc);
	return (0);
}

int	extract_value(char *token_str, char **var_value)
{
	*var_value = ft_strdup(token_str);
	return (0);
}

int	check_env_val_exists(t_environment *env, char *var_name)
{
	while (env)
	{
		if (ft_strcmp(var_name, env->name) == 0)
			return (1);
		else
			env = env->next;
	}
	return (0);
}
