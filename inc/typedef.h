/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:31:04 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/22 17:46:42 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

#include "minishell.h"
#include <stdbool.h>

typedef struct	s_environment
{
	char					*name;
	char					*value;
	struct s_environment	*next;
}				t_environment;

typedef enum	e_type
{
	UNDEFINED,
	PIPE,
	REDIRECT,
	ARG,
	CMD
}		t_type;

typedef struct	s_token
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

typedef struct	s_args
{
	char	**arg_array;
	char	**env_array;
	//char	**exec_path;
}				t_args;

/*typedef struct s_syntax_token
{
	struct s_syntax_token	*parent;
	struct s_syntax_token	*left;
	struct s_syntax_token	*right;
	int						input;
	int						output;
	t_token					*token;
}		t_syntax_token;*/

#endif
