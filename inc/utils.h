/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:16:09 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/20 18:08:55 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "minishell.h"

void	reset_list(t_token **tokens);
void	free_tokens(t_token *token);
int		ft_error(char *str, int errno);
void	clean_exit(t_token *token, char *msg);
void	sig_handler(int sig);
char	**ft_split_quotes(char const *s, char c);

# endif
