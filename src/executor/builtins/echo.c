/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                     +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:43:07 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/25 18:43:47 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	determine_echo(t_token *tokens)
{
	t_token	*temp;
	int		status;

	temp = tokens;
	status = 0;
	if (temp->next && temp->next->type == ARG)
	{
		status = echo(temp->right);
		return (status);
	}
	else
	{
		status = echo_no_arg(temp);
		return (status);
	}
	return (1);
}

int	echo(t_token *tokens)
{
	t_token	*temp;
	int		n_flag;

	temp = tokens;
	n_flag = 0;
	if (temp->type == ARG && ft_strcmp(temp->str, "-n") == 0)
	{
		n_flag = 1;
		temp = temp->next;
	}
	while (temp && temp->type == ARG)
	{
		printf("%s", temp->str);
		if (temp->has_space)
			printf(" ");
		temp = temp->next;
	}
	if (n_flag == 0)
		printf("\n");
	return (ft_error(NULL, 0));
}

int	echo_no_arg(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	(void)temp;
	printf("\n");
	return (ft_error(NULL, 0));
}
