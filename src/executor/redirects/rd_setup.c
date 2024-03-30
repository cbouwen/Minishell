/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:54:38 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/29 19:54:50 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	redirect_syntax_check(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIRECT)
		{
			if (temp->next->type == ARG)
			{
				if (ft_isdigit(temp->next->str[0]) == 1)
					return (ft_error("syntax error\n", 3));
			}
		}
		temp = temp->next;
	}
	return (rd_error_handler(0, NULL, NULL));
}

int	init_rd(t_token *tokens, t_rd_col *rd)
{
	t_token			*temp;
	t_rd_col	*temp_rd;

	temp = tokens;
	temp_rd = rd;
	temp_rd->input = ft_calloc(sizeof(char *), count_rd(temp) + 1);
	if (!temp_rd->input)
		return (rd_error_handler(12, NULL, rd));
	temp_rd->output = ft_calloc(sizeof(char *), count_rd(temp) + 1);
	if (!temp_rd->output)
		return (rd_error_handler(12, NULL, rd));
	temp_rd->input_size = 0;
	temp_rd->output_size = 0;
	temp_rd->i_fd = 0;
	temp_rd->o_fd = 0;
	temp_rd->file_exists = 0;
	temp_rd->coll_exists = true;
	temp_rd->c_stdin = 0;
	temp_rd->c_stdout = 0;
	return (rd_error_handler(0, NULL, rd));
}

int run_redirect(t_token *tokens, t_env *env, t_args *args)
{
	t_rd_col	rd;
	int			status;

	status = 0;
	while (tokens && tokens->type != PIPE)
	{
		printf("temp->str: %s\n", tokens->str);
		temp = tokens->next;
	}
	if (redirect_syntax_check(tokens) != 0)
		return (1);
	if (init_rd(tokens, &rd) != 0)
		return (1);
	if (fill_rd(tokens, &rd) != 0)
		return (1);
	if (open_input(&rd) != 0)
		return (1);
	if (open_output(&rd) != 0)
		return (1);
	status = rd_exec_setup(tokens, env, args, &rd);
	if (rd.coll_exists == true)
		free_rd(&rd);
	return (status);
}

