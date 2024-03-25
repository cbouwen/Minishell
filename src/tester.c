/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:47:47 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/07 15:47:15 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	test_syntax_tree(t_token *token, int pipes)
{
	int	i;

	i = 0;
	while (token->parent != NULL)
		token = token->next;
	printf("Parent contains this string: %s\nIts type is %u\nIts next string is
			%s\n\n", token->str, token->type, token->next->str);
	while (token->left != NULL)
	{
		if (token->left == NULL)
			break ;
		token = token->left;
		printf("Token to the left contains this string: %s\nIts type is %u\n\n",
				token->str, token->type);
	}
	while (token)
	{
		if (token->right == NULL)
			break ;
		token = token->right;
		printf("Token to the right contains this string: %s\nIts type is
				%u\n\n", token->str, token->type);
	}
	while (pipes != i)
	{
		printf("\nEnd of branch %i\n\n\n", i + 1);
		while (token->type != PIPE)
			token = token->parent;
		if (i == 1)
			token = token->parent;
		if (i == 2)
			token = token->parent;
		if (i == 3)
			token = token->parent;
		printf("Parent contains this string: %s\nIts type is
				%u\nIts pointer address is %p\n\n", token->str, token->type,
				token);
		while (token->right != NULL)
		{
			if (token->right == NULL)
				break ;
			token = token->right;
			printf("Token to the right contains this string: %s\nIts type is
					%u\n\n", token->str, token->type);
		}
		i++;
	}
	printf("\nEnd of branch %i\n\n\n", i + 1);
}

void	test_tokenizer(t_token *tokens)
{
	int	i;

	i = 1;
	while (tokens)
	{
		printf("Token %i contains this string: '%s'\nIts type is %u\n\n", i,
				tokens->str, tokens->type);
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
