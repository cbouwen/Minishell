/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:51:56 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/29 19:51:59 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

extern t_signal	g_signal;

int	free_rd(t_rd_col *rd)
{
	t_rd_col	*temp_rd;

	temp_rd = rd;
	if (temp_rd->coll_exists == false)
		return (0);
	if (temp_rd->input != NULL)
		free_array(temp_rd->input);
	if (temp_rd->output != NULL)
		free_array(temp_rd->output);
	temp_rd->coll_exists = false;
	return (0);
}

size_t count_rd(t_token *tokens)
{
	t_token	*temp;
	size_t	count;

	temp = tokens;
	debug_tm(temp);
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
//	if (g_signal.in_heredoc == true)
//		g_signal.in_heredoc = false;
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
