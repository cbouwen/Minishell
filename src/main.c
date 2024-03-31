/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:16:53 by cbouwen           #+#    #+#             */
/*   Updated: 2024/04/01 00:01:55 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_signal	g_signal;

int	run_minishell(t_env *env, char *input)
{
	t_token	*tokens;

	tokens = NULL;
	while (1)
	{
		tokenizer(input, &tokens);
		if (!tokens)
			break ;
		if (!(lexer(&tokens)))
			break ;
		parser(&tokens);
		expander(&tokens, env);
		g_signal.in_cmd = true;
		executor(tokens, env);
		g_signal.in_cmd = false;
		break ;
	}
	free_tokens(tokens);
	free(input);
	return (0);
}

int	minishell_loop(char **envp)
{
	t_env	*env;
	char	*input;

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
