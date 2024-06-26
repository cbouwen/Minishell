/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:31:04 by cbouwen           #+#    #+#             */
/*   Updated: 2024/04/01 00:10:05 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "minishell.h"
# include <stdbool.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef enum e_type
{
	UNDEFINED,
	PIPE,
	REDIRECT,
	ARG,
	CMD
}				t_type;

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

typedef struct s_args
{
	char	**arg_array;
	char	**env_array;
	int		fd[2];
	int		in_fd;
	int		pipe_count;
	int		a_stdout;
	int		a_stdin;
	t_token	*tokens;
	t_env	*env;
}				t_args;

typedef struct s_rd_col
{
	char	**input;
	int		input_size;
	char	**output;
	int		output_size;
	int		i_fd;
	int		o_fd;
	int		file_exists;
	bool	coll_exists;
	int		c_stdin;
	int		c_stdout;
	t_args	*args;
	t_token	*tokens;
	t_env	*env;
}				t_rd_col;

typedef struct s_signal
{
	int			err_no;
	bool		in_cmd;
	bool		in_heredoc;
	t_rd_col	*rd;
}				t_signal;

#endif
