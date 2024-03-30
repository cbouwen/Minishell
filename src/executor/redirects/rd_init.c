/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:51:31 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/29 20:01:01 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int fill_rd(t_token *tokens, t_rd_col *rd)
{
	t_token	*temp;
	t_rd_col	*temp_rd;
	int i;
	int j;

	temp = tokens;
	temp_rd = rd;
	i = -1;
	j = -1;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIRECT)
		{
			if (!ft_strcmp(temp->str, "<") || !ft_strcmp(temp->str, "<<"))
				fill_input(temp, temp_rd, ++i);
			else if (ft_strcmp(temp->str, ">") == 0)
				fill_out(temp, temp_rd, ++j, ">");
			else if (ft_strcmp(temp->str, ">>") == 0)
				fill_app(temp, temp_rd, ++j);
		}
		temp = temp->next;
	}
	rd->input_size = i + 1;
	rd->output_size = j + 1;
	return (rd_error_handler(0, NULL, rd));
}

int fill_input(t_token *tokens, t_rd_col *rd, int i)
{
	t_token			*temp;
	t_rd_col	*temp_rd;

	temp = tokens;
	temp_rd = rd;
	if (temp->type == REDIRECT)
	{
		if (ft_strcmp(temp->str, "<") == 0)
		{
			temp_rd->input[i] = ft_strdup(temp->next->str);
			if (!temp_rd->input[i])
				return (rd_error_handler(12, NULL, rd));
		}
		else if (ft_strcmp(temp->str, "<<") == 0)
		{
			return (fill_heredoc(temp, temp_rd, i));
		}
	}
	return (rd_error_handler(0, NULL, rd));
}

int	fill_heredoc(t_token *tokens, t_rd_col *rd, int i)
{
	t_token		*temp;
	t_rd_col	*temp_rd;
	char		*input;
	char		*temp_input;

	temp = tokens;
	temp_rd = rd;
	input = NULL;
	temp_input = NULL;
	input = ft_strdup("#");
	if (!input)
		return (rd_error_handler(12, NULL, rd));
	temp_input = strjoin_free(input, temp->next->str, 0);
	if (!temp_input)
	{
		free(input);
		return (rd_error_handler(12, NULL, rd));
	}
	free(input);
	input = temp_input;
	temp_rd->input[i] = input;
	return (rd_error_handler(0, NULL, rd));
}

int fill_out(t_token *tokens, t_rd_col *rd, int i, char *rd_type)
{
	t_token		*temp;
	t_rd_col	*temp_rd;
	char		**target;

	temp = tokens;
	temp_rd = rd;
	debug_tm(temp);
	if (temp->type == REDIRECT)
	{
		if (ft_strcmp(temp->str, rd_type) == 0)
		{
			if (ft_strcmp(rd_type, ">") == 0)
				target = &(temp_rd->output[i]);
			else
				return (0);
			*target = ft_strdup(temp->next->str);
			if (!*target)
				return (rd_error_handler(12, NULL, rd));
		}
	}
	return (rd_error_handler(0, NULL, rd));
}

int	fill_app(t_token *tokens, t_rd_col *rd, int i)
{
	t_token			*temp;
	t_rd_col	*temp_rd;
	char			*input;
	char			*temp_input;

	temp = tokens;
	temp_rd = rd;
	input = NULL;
	temp_input = NULL;
	input = ft_strdup("#");
	if (!input)
		return (rd_error_handler(12, NULL, rd));
	temp_input = strjoin_free(input, temp->next->str, 0);
	if (!temp_input)
	{
		free(input);
		return (rd_error_handler(12, NULL, rd));
	}
	free(input);
	input = temp_input;
	temp_rd->output[i] = input;
	return (rd_error_handler(0, NULL, rd));
}
