/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:16:53 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/20 16:52:01 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	run_minishell(t_environment *env, char	*input)
{
	t_token	*tokens;
	t_token	*head;
	//t_syntax_token	syntax_tree;
	(void)env;

	tokens = NULL;
	tokenizer(input, &tokens);
	lexer(&tokens);
	//parser(&tokens, &head);
	//expander(&tokens)
	//executor(tokens, env);
	//tester(env);
	test_tokenizer(tokens);
	free_tokens(tokens);
	free(input);
	return (0);
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
