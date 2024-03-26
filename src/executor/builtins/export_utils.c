/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                     +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:41:17 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/25 18:41:56 by matisse          ###   ########.fr       */
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
	if (!value)
		return (ft_error("export: malloc error\n", 12));
	sign_loc = value - token_str;
	*var_name = ft_substr(token_str, 0, sign_loc);
	return (ft_error(NULL, 0));
}

int	extract_value(char *token_str, char **var_value)
{
	*var_value = ft_strdup(token_str);
	if (!*var_value)
		return (ft_error("export: malloc error\n", 12));
	return (ft_error(NULL, 0));
}

/*0 if val exists
  1 if val doesn't exist*/
int	check_env_val_exists(t_environment *env, char *var_name)
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
	(void)token_str;
	(void)var_name;
	(void)var_value;
	printf("special export\n");
	/*int		sign_loc;
	char	*value;

	sign_loc = 0;
	value = NULL;
	value = ft_strchr(token_str, '=');
	if (!value)
		return (ft_error("export: malloc error\n", 12));
	sign_loc = value - token_str;
	*var_name = ft_substr(token_str, 0, sign_loc);
	*var_value = ft_strdup(value + 1);
	if (!*var_value)
		return (ft_error("export: malloc error\n", 12));
	return (ft_error(NULL, 0));*/
}
