/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:37:58 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/27 17:28:29 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "minishell.h"

int		parser(t_token **tokens);
void	parse_pipes(t_token *token);
//void	parse_redirects(t_token *tmp, t_token **tmp_head, int pipes);

#endif
