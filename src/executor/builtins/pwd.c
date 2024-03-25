/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:44:53 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/25 18:45:22 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	pwd(t_token *token)
{
	char	*cwd;

	(void)token;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_error("pwd: error retrieving current directory\n", 1));
	printf("%s\n", cwd);
	free(cwd);
	return (ft_error(NULL, 0));
}
