/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:42:34 by mlegendr          #+#    #+#             */
/*   Updated: 2024/04/01 00:42:49 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	exit_shell(t_token *tokens, t_env *env, t_args *args)
{
	if (args)
		free_args(args);
	clean_exit(tokens, env, NULL);
	return (0);
}
