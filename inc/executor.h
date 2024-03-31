/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:33:00 by mlegendr          #+#    #+#             */
/*   Updated: 2024/04/01 00:10:35 by matisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/*executor*/
int		executor(t_token *tokens, t_env *env);
int		builtin_executor(t_token *tokens, t_env *env, t_args *args);
int		check_pipes(t_token *tokens);
int		check_redirects(t_token *tokens);
int		run_basic_cmd(t_token *tokens, t_env *env, t_args *args);
int		run_builtin(t_token *tokens, t_env *env, t_args *args);
int		prep_cmd(t_token *tokens, t_env *env, t_args *args);

/*syntax checkers*/
int		exec_syntax_check(t_token *tokens);
int		determine_builtin(t_token *tokens);
int		check_env(t_token *tokens);
int		check_export(t_token *tokens);
int		check_unset(t_token *tokens);
int		check_last_char(char *str, char c);
int		check_first_char(char *str);
int		check_absolute_path(char *path);

/*echo*/
int		determine_echo(t_token *tokens);
int		echo(t_token *tokens);
int		echo_no_arg(t_token *tokens);

/*pwd*/
int		pwd(t_token *token);

/*env*/
int		print_env(t_token *tokens, t_env *env);

/*export*/
int		export_var(t_token *tokens, t_env *env);
int		check_env_val_exists(t_env *env, char *var_name);
int		extract_name(char *token_str, char **var_name);
int		extract_value(char *token_str, char **var_value);
int		update_env_val(t_env *env, char *var_name, char *var_value, bool cd);
int		add_env_val(t_env *env, char *var_name, char *var_value);
int		special_export(char *token_str, char **var_name, char **var_value);

/*unset*/
int		unset_var(t_token *tokens, t_env *env);
int		delete_var(t_env *env, char *var_name);

/*cd*/
int		change_dir(t_token *tokens, t_env *env);
int		go_home(t_env *env);
int		go_oldpwd(t_token *tokens, t_env *env);
int		get_env_val(t_env *env, char *var_name, char **var_value);
int		go_dir(char *path, t_env *env);
int		update_pwd(t_env *env, char *path);
int		free_and_return(char *str1, char *str2, int err_no);

/*exit*/
int		exit_shell(t_token *tokens, t_env *env, t_args *args);

/*execve*/
size_t	count_tokens(t_token *tokens);
int		execve_executor(t_token *tokens, t_args *args);
int		fill_args(t_args *args, t_token *tokens);
int		free_args(t_args *args);
int		free_args_full(t_args *args, int err_no);
int		run_execve(t_args *args);
size_t	count_env(t_env *env);
int		init_args(t_args *args, t_token *tokens, t_env *env);
int		fill_env(t_args *args, t_env *env);
char	*strjoin_free(char *s1, char *s2, int free_str);
int		find_path(t_args *args);
int		split_path(t_args *args, char ***exec_path);
int		free_array(char **array);
int		assemble_path(t_args *args);
int		true_path_ass(char *path, t_args *args);
int		handle_rel_path(t_args *args);
int		create_exec_path(t_args *args, char **exec_path);
int		path_error_handler(int err_no);

/*new redirect stuff*/
int		redirect_syntax_check(t_token *tokens);
int		fill_rd(t_token *tokens, t_rd_col *rd);
int		fill_input(t_token *temp, t_rd_col *rd, int i);
int		fill_heredoc(t_token *tokens, t_rd_col *rd, int i);
int		fill_out(t_token *tokens, t_rd_col *rd, int i, char *rd_type);
int		fill_app(t_token *tokens, t_rd_col *rd, int i);
size_t	count_rd(t_token *tokens);
int		init_rd(t_token *tokens, t_rd_col *rd, t_args *args, t_env *env);
int		rd_error_handler(int err_no, char *str, t_rd_col *rd);
int		open_output(t_rd_col *rd);
int		open_input(t_rd_col *rd);
int		open_heredoc(char *input, t_rd_col *rd);
int		free_rd(t_rd_col *rd);
int		rd_exec_setup(t_token *tok, t_env *env, t_args *arg, t_rd_col *rd);
int		input_rd(t_token *tok, t_env *env, t_args *arg, t_rd_col *rd);
int		output_rd(t_token *tok, t_env *env, t_args *arg, t_rd_col *rd);
int		super_redirect(t_token *tok, t_env *env, t_args *arg, t_rd_col *rd);
int		run_redirect(t_token *tokens, t_env *env, t_args *args);
int		free_rd_full(t_rd_col *temp_rd);
void	hd_sig(int sig);

/*pipes*/
/*pipe_utils*/
int		move_to_next(t_token **tokens);
int		count_pipes(t_token *tokens);
int		real_pipe(t_token *tokens, t_env *env, t_args *args);
int		pipe_error_handler(int err_no);

/*pipe_parser*/
int		pipe_decider(t_token **tokens, t_env *env, t_args *args);
int		run_piped_cmd(t_token **tokens, t_env *env, t_args *args);
int		run_cmd(t_token *tokens, t_env *env, t_args *args);

/*cool_cat*/
bool	check_cat(t_token *tokens);
int		cool_cat(t_token **tokens, t_env *env, t_args *args);
int		count_cat(t_token *tokens);
bool	check_cat_no_args(t_token *tokens);
int		run_fake_cat(int count);

#endif
