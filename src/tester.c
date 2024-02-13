/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:47:47 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/13 16:52:45 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	tester(t_environment *envp)
{
	while (envp)
	{
		printf("%s=%s\n", envp->name, envp->value);
		envp = envp->next;
	}
}
