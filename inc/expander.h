/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:49:50 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/05 16:37:59 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
#define EXPANDER_H

#include "minishell.h"

int	find_quote(t_token *token, char c);
int	count_quotes(char *str);
int	expander(t_token **tokens, t_environment *env);
int	handle_question_mark(t_token **tokens);

#endif
