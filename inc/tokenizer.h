/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:33:14 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/15 16:58:17 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

#include "minishell.h"

int		tokenizer (char *input, t_token **tokens);
char	**ft_free(char **s2, int count);
char	**split_args(char const *s, char c);



#endif
