/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:23:46 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/15 19:20:40 by mlegendr         ###   ########.fr       */
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
		else
			go_dir(temp->str, env);
	}
	else
		return (assign_and_handle_error(CD, 1));
	return (0);
}

int	go_dir(char *path, t_environment *env)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (free_and_return(current_pwd, NULL));
	if (chdir(path) == -1)
		return (free_and_return(current_pwd, NULL));
	if (update_pwd(env, current_pwd) != 0)
		return (free_and_return(current_pwd, NULL));
	free(current_pwd);
	return (0);
}

int	go_home(t_environment *env)
{
	char	*home_path;
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (free_and_return(current_pwd, NULL));
	if (get_env_val(env, "HOME", &home_path) == 1)
		return (free_and_return(current_pwd, NULL));
	if (!home_path)
		return (free_and_return(current_pwd, NULL));
	if (chdir(home_path) == -1)
		return (free_and_return(current_pwd, home_path));
	if (update_pwd(env, current_pwd) != 0)
		return (free_and_return(current_pwd, home_path));
	free(home_path);
	free(current_pwd);
	return (0);
}

int	go_oldpwd(t_token *tokens, t_environment *env)
{
	char	*new_pwd;
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (free_and_return(current_pwd, NULL));
	if (get_env_val(env, "OLDPWD", &new_pwd) == 1)
		return (free_and_return(current_pwd, NULL));
	if (!new_pwd)
		return (free_and_return(current_pwd, NULL));
	if (chdir(new_pwd) == -1)
		return (free_and_return(current_pwd, new_pwd));
	if (update_pwd(env, current_pwd) != 0)
		return (free_and_return(current_pwd, new_pwd);
	ft_putstr_fd(new_pwd, tokens->output);
	ft_putstr_fd("\n", tokens->output);
	free(new_pwd);
	free(current_pwd);
	return (0);
}
