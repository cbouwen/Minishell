/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:16:53 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/26 14:10:50 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_signal	g_signal;

int	run_minishell(t_environment *env, char *input)
{
	t_token	*tokens;

	tokens = NULL;
	while (1)
	{
		tokenizer(input, &tokens);
		if (!tokens)
			break;
		if (!(lexer(&tokens)))
			break ;
		parser(&tokens);
		expander(&tokens, env);
		//test_tokenizer(tokens);
		g_signal.in_cmd = true;
		executor(tokens, env);
		g_signal.in_cmd = false;
		//exit_status = executor(tokens, env);
		//tester(env);
		//test_tokenizer(tokens);
		//test_syntax_tree(tokens, pipe_counter(tokens));
		break ;
	}
	free_tokens(tokens);
	free(input);
	return (0);
}

int	minishell_loop(char **envp)
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
			break ;
		}
		if (ft_strcmp(input, "") == 0)
		{
			free(input);
			continue ;
		}
		if (ft_strcmp(input, "exit") == 0)
			clean_exit(NULL, env, NULL);
		add_history(input);
		run_minishell(env, input);
	}
	free_env(env);
	rl_clear_history();
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	g_signal.err_no = 0;
	g_signal.in_cmd = false;
	g_signal.in_heredoc = false;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell_loop(envp);
}
