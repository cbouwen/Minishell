/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:33:00 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/14 20:38:48 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

void	echo(t_token *tokens);
void	echo_no_arg(t_token *tokens);
void	pwd(t_token *token);
int		executor(t_token *tokens, t_environment *env);
void	print_env(t_token *tokens, t_environment *env);
void	env_error_msg(t_token *tokens);
int		export_var(t_token *tokens, t_environment *env);
int		check_env_val_exists(t_environment *env, char *var_name);
int		extract_name(char *token_str, char **var_name);
int		extract_value(char *token_str, char **var_value);
int		update_env_val(t_environment *env, char *var_name, char *var_value);
int		add_env_val(t_environment *env, char *var_name, char *var_value);
int		unset_var(t_token *tokens, t_environment *env);
int		delete_var(t_environment *env, char *var_name);
int		change_dir(t_token *tokens, t_environment *env);
int		go_home(t_environment *env);
int		go_oldpwd(t_token *tokens, t_environment *env);
int		get_env_val(t_environment *env, char *var_name, char **var_value);

#endif
