/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cool_cat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:57:54 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/31 23:58:29 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	cool_cat(t_token **tokens, t_env *env, t_args *args)
{
	t_token	*temp;
	t_env	*temp_env;
	t_args	*temp_args;
	int		status;
	int		count;

	status = 0;
	count = 0;
	temp = *tokens;
	temp_env = env;
	temp_args = args;
	while (temp)
	{
		if (check_cat_no_args(temp))
		{
			count++;
			move_to_next(tokens);
		}
		temp = temp->next;
	}
	status = run_piped_cmd(tokens, temp_env, temp_args);
	run_fake_cat(count);
	return (status);
}

int	run_fake_cat(int count)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (i < count)
	{
		line = readline("");
		if (line != NULL)
		{
			printf("%s\n", line);
			free(line);
			i++;
		}
		else
			break ;
	}
	return (0);
}
