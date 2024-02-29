/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:47:47 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/29 13:56:23 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	test_syntax_tree(t_token *token)
{
	while (token->parent != NULL)
		token = token->next;
	printf("Parent contains this string: %s\nIts type is %u\n\n", token->str, token->type);
	while (token->left != NULL)
	{
		if (token->left == NULL)
			break;
		token = token->left;
		printf("Token to the left contains this string: %s\nIts type is %u\n\n", token->str, token->type);
	}
	while (token)
	{
		if (token->right == NULL)
			break;
		token = token->right;
		printf("Token to the right contains this string: %s\nIts type is %u\n\n", token->str, token->type);
	}
	while (token->parent != NULL)
		token = token->parent;
	while (token->right != NULL)
	{
		if (token->right == NULL)
			break;
		token = token->right;
		printf("Token to the right contains this string: %s\nIts type is %u\n\n", token->str, token->type);
	}

}


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
