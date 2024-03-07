/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:49:50 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/07 16:21:26 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
#define EXPANDER_H

#include "minishell.h"

//char	*execute_question_mark();
char	*find_env(char *str, t_environment *env);
int	find_quote(t_token *token, char c);
int	count_quotes(char *str);
int	expander(t_token **tokens, t_environment *env);
int	handle_question_mark(t_token **tokens);
int	expand_double_quote(t_token **tokens, t_environment *env);
void	remove_quotes(t_token **tokens, char c);
int	handle_question_mark(t_token **tokens);
char	*ft_strjoin_quotes(char *s1, char *s2);

#endif
