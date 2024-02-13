/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:18:10 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/13 15:50:45 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_env_node(t_environment *env)
{
	if (!env)
		return ;
	if (env->value)
		free(env->value);
	if (env->name)
		free(env->name);
	free(env);
}

void	free_env(t_environment *env)
{
	t_environment	*tmp;

	while (env)
	{
		tmp = env->next;
		free_env_node(env);
		env = tmp;
	}
}

t_environment	*get_env_node(t_environment *head, char *name)
{
	while (head && ft_strcmp(head->name, name))
		head = head->next;
	return (head);
}
