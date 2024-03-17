/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:56:37 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/11 18:47:03 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_var(t_token *tokens, t_environment *env)
{
	if (check_env_val_exists(env, tokens->str) == 1)
		return (ft_error("unset", 1);
	delete_var(env, tokens->str);
	return (ft_error(NULL, 0));
}

int	delete_var(t_environment *env, char *var_name)
{
	t_environment	*current;
	t_environment	*previous;

	current = env;
	previous = NULL;
	while (env)
	{
		if (ft_strcmp(var_name, current->name) == 0)
		{
			if (previous == NULL)
				env = current->next;
			else
				previous->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	return (ft_error(NULL, 1));
}
