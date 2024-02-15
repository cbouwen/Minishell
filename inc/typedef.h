/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:31:04 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/15 15:42:44 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

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
	struct s_token	*next;
}				t_token;



#endif
