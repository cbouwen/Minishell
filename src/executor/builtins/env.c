/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:45:38 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/31 23:59:57 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	print_env(t_token *tokens, t_env *env)
{
	t_token	*temp;
	t_env	*temp_env;

	temp = tokens;
	temp_env = env;
	if (temp->next && temp->next->type == ARG
		&& ft_strcmp(temp->next->str, "env") != 0)
		return (ft_error("env: too many arguments\n", 1));
	while (temp_env)
	{
		printf("%s=%s\n", temp_env->name, temp_env->value);
		temp_env = temp_env->next;
	}
	return (ft_error(NULL, 0));
}
