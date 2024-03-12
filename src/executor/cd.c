/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:23:46 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/12 18:44:43 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	change_dir(t_token *tokens, t_environment *env)
{
	t_token = *temp;

	temp = tokens;
	if (!temp->next || temp->next->type != "ARG")
		head_home(temp, env);
}

int	head_home(t_token *tokens, t_environment *env)
{

}
