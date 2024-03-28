/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:18:10 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/28 21:19:21 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_env_node(t_env *env)
{
	if (!env)
		return ;
	if (env->value)
		free(env->value);
	if (env->name)
		free(env->name);
	free(env);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free_env_node(env);
		env = tmp;
	}
}

t_env	*get_env_node(t_env *head, char *name)
{
	while (head && ft_strcmp(head->name, name))
		head = head->next;
	return (head);
}
