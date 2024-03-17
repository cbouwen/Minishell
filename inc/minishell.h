/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:07 by cbouwen           #+#    #+#             */
/*   Updated: 2024/03/08 16:27:40 by cbouwen          ###   ########.fr       */
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


t_environment				*env_parser(char *envp[]);
void						free_env_node(t_environment *env);
void						free_env(t_environment *env);
t_environment				*get_env_node(t_environment *head, char *name);
t_environment				*create_node(char *name, char *value);
void						ft_lstadd_back_ms(t_environment **lst, t_environment *new);

//tester
void						tester(t_environment *envp);
void						test_tokenizer(t_token *tokens);
void						test_syntax_tree(t_token *token, int pipes);

#endif

//Quick test to see if I can merge now
