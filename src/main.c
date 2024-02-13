/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:16:53 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/13 17:51:22 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	run_minishell(t_environment *env, char	*input)
{
	(void)env;
	if (ft_strcmp(input, "q"))
		ft_printf("hi\n");
	else
		tester(env);
	return (1);
}


int	minishell_loop(char *envp[])
{
	t_environment	*env;
	char			*input;

	env = env_parser(envp);
	while (1)
	{
		input = readline("Minishell: ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (ft_strcmp(input, "") == 0)
		{
			free(input);
			continue;
		}
		add_history(input);
		run_minishell(env, input);
	}

	free_env(env);
	rl_clear_history();
	return (0);
}


int	main(int argc, char **argv, char *envp[])
{
	(void)argc;
	(void)argv;
	minishell_loop(envp);
}
