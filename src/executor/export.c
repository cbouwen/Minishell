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
	var_name = NULL;
	var_value = NULL;
	extract_name(temp->str, &var_name);
	extract_value(temp->next->str, &var_value);
	if (check_env_val_exists(temp_env, var_name) == 0)
		update_env_val(temp_env, var_name, var_value);
	else
		add_env_val(temp_env, var_name, var_value);
	free(var_name);
	free(var_value);
	return (0);	
}
