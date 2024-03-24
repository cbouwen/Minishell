/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:23:46 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/21 18:25:59 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	change_dir(t_token *tokens, t_environment *env)
{
	t_token	*temp;
	int		status;

	temp = tokens;
	status = 0;
	if (!temp->next || temp->next->type != ARG)
	{
		status = go_home(env);
		return (ft_error(NULL, status));
	}
	temp = temp->next;
	if (temp->type == ARG)
	{
		if (ft_strcmp(temp->str, "-") == 0)
			status = go_oldpwd(temp, env);
		else if (ft_strcmp(temp->str, "~") == 0
			|| ft_strcmp(temp->str, "--") == 0)
			status = go_home(env);
		else
			status = go_dir(temp->str, env);
	}
	else
		return (ft_error("cd: unexpected error\n", 1));
	return (ft_error(NULL, status));
}

int	go_dir(char *path, t_environment *env)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (free_and_return(current_pwd, NULL, 12));
	if (chdir(path) == -1)
		return (free_and_return(current_pwd, NULL, 2));
	if (update_pwd(env, current_pwd) != 0)
		return (free_and_return(current_pwd, NULL, 1));
	free(current_pwd);
	return (ft_error(NULL, 0));
}

int	go_home(t_environment *env)
{
	char	*home_path;
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (free_and_return(current_pwd, NULL, 1));
	if (get_env_val(env, "HOME", &home_path) == 1)
		return (free_and_return(current_pwd, NULL, 1));
	if (!home_path)
		return (free_and_return(current_pwd, NULL, 12));
	if (chdir(home_path) == -1)
		return (free_and_return(current_pwd, home_path, 2));
	if (update_pwd(env, current_pwd) != 0)
		return (free_and_return(current_pwd, home_path, 1));
	free(home_path);
	free(current_pwd);
	return (ft_error(NULL, 0));
}

int	go_oldpwd(t_token *tokens, t_environment *env)
{
	char	*new_pwd;
	char	*current_pwd;

	(void)tokens;
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (free_and_return(current_pwd, NULL, 12));
	if (get_env_val(env, "OLDPWD", &new_pwd) == 1)
		return (free_and_return(current_pwd, NULL, 1));
	if (!new_pwd)
		return (free_and_return(current_pwd, NULL, 12));
	if (chdir(new_pwd) == -1)
		return (free_and_return(current_pwd, new_pwd, 2));
	if (update_pwd(env, current_pwd) != 0)
		return (free_and_return(current_pwd, new_pwd, 1));
	printf("%s\n", new_pwd);
	/*ft_putstr_fd(new_pwd, tokens->output);
	ft_putstr_fd("\n", tokens->output);*/
	free(new_pwd);
	free(current_pwd);
	return (ft_error(NULL, 0));
}
