/*header pls*/

#include "../../inc/minishell.h"

/*
** check_absolute_path (status) possible return values:
** @return 12: malloc error
** @return 1: absolute path
** @return 2: relative path
** @return -1: not an executable file
*/

int	assemble_path(t_args *args)
{
	int		status;

	status = check_absolute_path(args->arg_array[0], args);
	if ( status== 12)
		return (12);
	if (status == -1)
		return (1);
	if (status == 1)
		return (2);
	if (status == 2)
		return (handle_rel_path(args));
	return (0);
}

int	handle_rel_path(t_args *args)
{
	int	status;

	status = split_path(args);
	if (status == 3)
		return (3);
	if (status == -2)
		return (-2);
	return (create_exec_path(args));
}

int	create_exec_path(t_args *args)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (args->exec_path[++i])
	{
		status = true_path_ass(args->exec_path[i], args);
		if (status == 0)
			return (2);
		else if (status == 12)
			return (12);
	}
	return(4);
}
