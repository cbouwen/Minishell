/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:23:46 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/14 20:44:02 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	change_dir(t_token *tokens, t_environment *env)
{
	t_token	*temp;

	temp = tokens;
	if (!temp->next || temp->next->type != ARG)
	{
		go_home(env);
		return (0);
	}
	temp = temp->next;
	if (temp->type == ARG)
	{
		if (ft_strcmp(temp->str, "-") == 0)
			go_oldpwd(temp, env);
		else if (ft_strcmp(temp->str, "~") == 0
			|| ft_strcmp(temp->str, "--") == 0)
			go_home(env);
		else if (temp->type == ARG)
			if (chdir(temp->str) == -1)
				return (errno);
		else
			return (1);
	}
	return (0);
}

int	go_home(t_environment *env)
{
	char	*home_path;
	char	*oldpwd;
	char	*pwd;

	if (get_env_val(env, "HOME", &home_path) == 1)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (!home_path)
		return (1);
	if (chdir(home_path) == -1)
		return (errno);
	update_env_val(env, "OLDPWD", oldpwd);
	pwd = getcwd(NULL, 0);
	update_env_val(env, "PWD", pwd);
	free(oldpwd);
	free(pwd);
	free(home_path);
	return (0);
}

int	go_oldpwd(t_token *tokens, t_environment *env)
{
	char	*new_pwd;
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (get_env_val(env, "OLDPWD", &new_pwd) == 1)
		return (1);
	if (chdir(new_pwd) == -1)
		return (errno);
	update_env_val(env, "PWD", new_pwd);
	update_env_val(env, "OLDPWD", current_pwd);
	ft_putstr_fd(new_pwd, tokens->output);
	ft_putstr_fd("\n", tokens->output);
	free(current_pwd);
	free(new_pwd);
	return (0);
}
