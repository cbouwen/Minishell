/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:37:58 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/25 15:30:08 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

int		parser(t_token **tokens);
void	parse_pipes(t_token *token);
void	first_redirect(t_token *token);
void	redirect_right(t_token *token);
int		pipe_counter(t_token *tmp);

#endif
