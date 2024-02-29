/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:37:58 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/29 13:27:00 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "minishell.h"

int		parser(t_token **tokens);
void	parse_pipes(t_token *token);
void	redirect_pipes(t_token *token, int pipes);
void	redirect_no_pipes(t_token *token);

#endif
