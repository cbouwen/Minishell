/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:07 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/19 13:41:40 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/Libft/libft.h"
# include "typedef.h"
# include "tokenizer.h"
# include "utils.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

int							ft_error(char *str);
t_environment				*env_parser(char *envp[]);
void						free_env_node(t_environment *env);
void						free_env(t_environment *env);
t_environment				*get_env_node(t_environment *head, char *name);

//tester
void						tester(t_environment *envp);
void						test_tokenizer(t_token *tokens);

#endif
