/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:47:47 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/19 13:42:44 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	test_tokenizer(t_token *tokens)
{
	int	i;

	i = 1;
	while (tokens)
	{
		printf("Token %i contains this string: %s\n", i, tokens->str);
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
