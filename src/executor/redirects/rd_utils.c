/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:51:56 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/31 23:45:09 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	free_rd(t_rd_col *temp_rd)
{
	if (temp_rd->coll_exists == false)
		return (0);
	free_array(temp_rd->input);
	free_array(temp_rd->output);
	temp_rd->coll_exists = false;
	return (0);
}

int	free_rd_full(t_rd_col *temp_rd)
{
	if (temp_rd->coll_exists == false)
		return (0);
	free_array(temp_rd->input);
	free_array(temp_rd->output);
	free_tokens(temp_rd->tokens);
	free_env(temp_rd->env);
	free_args(temp_rd->args);
	temp_rd->coll_exists = false;
	return (0);
}

size_t	count_rd(t_token *tokens)
{
	t_token	*temp;
	size_t	count;

	temp = tokens;
	count = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIRECT)
			count++;
		temp = temp->next;
	}
	return (count);
}

int	rd_error_handler(int err_no, char *str, t_rd_col *rd)
{
	if (err_no == 12)
		ft_error("malloc failed\n", 12);
	else if (err_no == 0)
		ft_error(NULL, 0);
	else if (err_no == 2)
	{
		printf("bash: %s", str);
		ft_error(": No such file or directory\n", 1);
	}
	else if (err_no == -1)
		ft_error("rd: Unexpected error\n", -1);
	if (rd && err_no != 0)
		free_rd(rd);
	return (ft_error(NULL, err_no));
}
