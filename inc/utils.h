/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:16:09 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/06 13:49:38 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "minishell.h"

void	reset_list(t_token **tokens);
void	free_tokens(t_token *token);
int		ft_error(char *str);
void	clean_exit(t_token *token, char *msg);
void	sig_handler(int sig);
char	**ft_split_quotes(char const *s, char c);
void	init_err(t_err *err);
int		assign_and_handle_error(t_err_type type, int err_no)

# endif
