/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:16:53 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/13 16:48:36 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	t_environment	*env;

	(void)argc;
	(void)argv;
	env = env_parser(envp);
	tester(env);
	free_env(env);
}
