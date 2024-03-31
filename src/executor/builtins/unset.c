/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:56:37 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/28 21:19:21 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	unset_var(t_token *tokens, t_env *env)
{
	int	status;

	status = 0;
	while (tokens && tokens->type == ARG)
	{
		if (tokens->type == ARG)
			if (check_env_val_exists(env, tokens->str) == 0)
				status = delete_var(env, tokens->str);
		tokens = tokens->next;
	}
	return (ft_error(NULL, status));
}

int	delete_var(t_env *env, char *var_name)
{
	t_env	*current;
	t_env	*previous;

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
	return (ft_error("unset: unexpected error\n", 1));
}
