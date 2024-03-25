/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:31:04 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/25 15:28:52 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "minishell.h"
# include <stdbool.h>

typedef struct s_environment
{
	char					*name;
	char					*value;
	struct s_environment	*next;
}				t_environment;

typedef enum e_type
{
	UNDEFINED,
	PIPE,
	REDIRECT,
	ARG,
	CMD
}		t_type;

typedef struct s_token
{
	char			*str;
	t_type			type;
	int				input;
	int				output;
	bool			has_space;
	struct s_token	*parent;
	struct s_token	*left;
	struct s_token	*right;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

#endif
