/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:33:00 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/22 20:30:14 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/*executor*/
int			executor(t_token *tokens, t_environment *env);
int			builtin_executor(t_token *tokens, t_environment *env);
int			check_pipes(t_token *tokens);
int			check_redirects(t_token *tokens);
int			run_basic_cmd(t_token *tokens, t_environment *env, t_args *args);
int			run_builtin(t_token *tokens, t_environment *env);
int			prep_cmd(t_token *tokens, t_environment *env, t_args *args);

/*redirects*/
int			run_redirects(t_token *tokens, t_environment *env, t_args *args);
int			determine_redirect(t_token *tokens, t_args *args);
int			determine_file(t_token *tokens, t_args *args);
int			heredoc_setup(t_token *tokens, t_args *args);
int			heredoc_no_redirect(t_token *tokens, t_args *args);
int			heredoc_redirect(t_token *tokens, t_args *args);
int			check_file_exists(t_args *args);
int			open_file(t_args *args);
int			setup_heredoc(t_token *tokens, t_args *args);
int			redirect_input(t_token *tokens, t_environment *env, t_args *args);
int			redirect_output(t_token *tokens, t_environment *env, t_args *args);
int			redirect_append(t_token *tokens, t_environment *env, t_args *args);

/*syntax checkers*/
int			exec_syntax_check(t_token *tokens);
int			determine_builtin(t_token *tokens);
int			check_env(t_token *tokens);
int			check_export(t_token *tokens);
int			check_unset(t_token *tokens);
int			check_last_char(char *str, char c);
int			check_first_char(char *str);
int			check_absolute_path(char *path);

/*echo*/
int			determine_echo(t_token *tokens);
int			echo(t_token *tokens);
int			echo_no_arg(t_token *tokens);

/*pwd*/
int			pwd(t_token *token);

/*env*/
int			print_env(t_token *tokens, t_environment *env);

/*export*/
int			export_var(t_token *tokens, t_environment *env);
int			check_env_val_exists(t_environment *env, char *var_name);
int			extract_name(char *token_str, char **var_name);
int			extract_value(char *token_str, char **var_value);
int			update_env_val(t_environment *env, char *var_name, char *var_value, bool cd);
int			add_env_val(t_environment *env, char *var_name, char *var_value);

/*unset*/
int			unset_var(t_token *tokens, t_environment *env);
int			delete_var(t_environment *env, char *var_name);

/*cd*/
int			change_dir(t_token *tokens, t_environment *env);
int			go_home(t_environment *env);
int			go_oldpwd(t_token *tokens, t_environment *env);
int			get_env_val(t_environment *env, char *var_name, char **var_value);
int			go_dir(char *path, t_environment *env);
int			update_pwd(t_environment *env, char *path);
int			free_and_return(char *str1, char *str2, int err_no);

/*execve*/
size_t		count_tokens(t_token *tokens);
int			execve_executor(t_token *tokens, t_args *args);
int			fill_args(t_args *args, t_token *tokens);
int			free_args(t_args *args);
int			run_execve(t_args *args);
size_t		count_env(t_environment *env);
int			init_args(t_args *args);
int			fill_env(t_args *args, t_environment *env);
char		*strjoin_free(char *s1, char *s2, int free_str);
int			find_path(t_args *args);
int			split_path(t_args *args, char ***exec_path);
int			free_array(char **array);
int			assemble_path(t_args *args);
int			true_path_ass(char *path, t_args *args);
int			handle_rel_path(t_args *args);
int			create_exec_path(t_args *args, char **exec_path);
int			path_error_handler(int err_no);

void	printf_args_env(t_args *args);

#endif
