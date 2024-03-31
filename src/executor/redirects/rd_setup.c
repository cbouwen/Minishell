/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:54:38 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/31 23:44:09 by matisse          ###   ########.fr       */
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

int	init_rd(t_token *tokens, t_rd_col *rd, t_args *args, t_env *env)
{
	rd->input = ft_calloc(sizeof(char *), count_rd(tokens) + 1);
	if (!rd->input)
		return (rd_error_handler(12, NULL, rd));
	rd->output = ft_calloc(sizeof(char *), count_rd(tokens) + 1);
	if (!rd->output)
		return (rd_error_handler(12, NULL, rd));
	rd->input_size = 0;
	rd->output_size = 0;
	rd->i_fd = 0;
	rd->o_fd = 0;
	rd->file_exists = 0;
	rd->coll_exists = true;
	rd->c_stdin = 0;
	rd->c_stdout = 0;
	rd->tokens = tokens;
	rd->args = args;
	rd->env = env;
	return (rd_error_handler(0, NULL, rd));
}

int	run_redirect(t_token *tokens, t_env *env, t_args *args)
{
	t_token		*temp;
	t_env		*temp_env;
	t_args		*temp_args;
	t_rd_col	rd;
	int			status;

	temp = tokens;
	temp_env = env;
	temp_args = args;
	status = 0;
	if (redirect_syntax_check(temp) != 0)
		return (1);
	if (init_rd(temp, &rd, temp_args, temp_env) != 0)
		return (1);
	if (fill_rd(temp, &rd) != 0)
		return (1);
	if (open_input(&rd) != 0)
		return (1);
	if (open_output(&rd) != 0)
		return (1);
	status = rd_exec_setup(temp, temp_env, temp_args, &rd);
	if (rd.coll_exists == true)
		free_rd(&rd);
	return (status);
}
