/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:16:53 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/07 15:54:37 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_err;

int	run_minishell(t_environment *env, char	*input)
{
	t_token	*tokens;

	tokens = NULL;
	while (1)
	{
		tokenizer(input, &tokens);
		if (!(lexer(&tokens)))
			break;
		parser(&tokens);
		expander(&tokens, env);
		executor(tokens, env);
		//exit_status = executor(tokens, env);
		//tester(env);
		//test_tokenizer(tokens);
		//test_syntax_tree(tokens, pipe_counter(tokens));
		break;
	}
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
		if (ft_strcmp(input, "exit") == 0)
			clean_exit(NULL, NULL);
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

	g_err = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	minishell_loop(envp);
}
