/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:47:47 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/20 14:51:36 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	test_tokenizer(t_token *tokens)
{
	int	i;

	i = 1;
	while (tokens)
	{
		printf("Token %i contains this string: %s\nIts type is %u\n\n", i, tokens->str, tokens->type);
		tokens = tokens->next;
		i++;
	}
}


void	tester(t_environment *envp)
{
	while (envp)
	{
		printf("%s=%s\n", envp->name, envp->value);
		envp = envp->next;
	}
}
