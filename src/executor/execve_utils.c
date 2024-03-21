/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <mlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:08:54 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/21 20:43:19 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int	execve_executor(t_token *tokens, t_args *args)
{
	int	status;
	
	(void)tokens;
	status = 0;
	status = run_execve(args);
	//free_args(args);
	return (status);
}

int	run_execve(t_args *args)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(args->arg_array[0], args->arg_array, args->env_array) == -1)
			exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
            return (ft_error(NULL, WEXITSTATUS(status)));
        else
            return (0);
	}
	return (status);
}
