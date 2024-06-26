/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:07 by cbouwen           #+#    #+#             */
/*   Updated: 2024/04/01 12:31:11 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/Libft/libft.h"
# include "typedef.h"
# include "tokenizer.h"
# include "utils.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# define WR O_WRONLY
# define CR O_CREAT
# define TR O_TRUNC
# define RW O_RDWR
# define AP O_APPEND
# define RD O_RDONLY

extern t_signal	g_signal;

t_env	*env_parser(char *envp[]);
void	free_env_node(t_env *env);
void	free_env(t_env *env);
t_env	*get_env_node(t_env *head, char *name);
t_env	*create_node(char *name, char *value);
void	ft_lstadd_back_ms(t_env **lst, t_env *new);
void	heredoc_handler(int sig);

#endif
