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
	extract_name(temp, &var_name);
	printf("export_var: tokens->str: %s\n", temp->str);
	extract_value(temp, &var_value);
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

int	extract_name(t_token *tokens, char **var_name)
{
	int		sign_loc;
	char	*value;

	sign_loc = 0;
	value = NULL;
	if (tokens->type == ARG)
	{
		value = ft_strchr(tokens->str, '=');
		if (!value)
			return (1);
	}
	else
		return (1);
	sign_loc = value - tokens->str;
	*var_name = ft_substr(tokens->str, 0, sign_loc);
	return (0);
}

int	extract_value(t_token *tokens, char **var_value)
{
	int		sign_loc;
	char	*value;

	sign_loc = 0;
	value = NULL;
	printf("extract_value: tokens->str: %s\n", tokens->str);
	if (tokens->type == ARG)
	{
		value = ft_strchr(tokens->str, '=');
		if (!value)
			return (1);
	}
	else
		return (1);
	printf("extract_value: value: %s\n", value);
	sign_loc = value - tokens->str;
	printf("extract_value: sign_loc: %d\n", sign_loc);
	*var_value = ft_substr(tokens->str, sign_loc + 1, ft_strlen(tokens->str) - sign_loc);
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
