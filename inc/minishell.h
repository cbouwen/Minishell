/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:07 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/29 16:12:34 by cbouwen          ###   ########.fr       */
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

# define W_C_T (O_WRONLY | O_CREAT | O_TRUNC)

extern t_signal	g_signal;

//int				ft_error(char *str);
t_env	*env_parser(char *envp[]);
void			free_env_node(t_env *env);
void			free_env(t_env *env);
t_env	*get_env_node(t_env *head, char *name);
t_env	*create_node(char *name, char *value);
void			ft_lstadd_back_ms(t_env **lst, t_env *new);
void heredoc_handler(int sig);

//tester
void			tester(t_env *envp);
void			test_tokenizer(t_token *tokens);
void			test_syntax_tree(t_token *token, int pipes);

#endif

//Quick test to see if I can merge now
