/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:04:13 by cbouwen           #+#    #+#             */
/*   Updated: 2024/04/01 00:04:39 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_error(char *str, int err_no)
{
	g_signal.err_no = err_no;
	if (g_signal.err_no == 0)
		return (0);
	if (str)
		printf("%s", str);
	return (err_no);
}
