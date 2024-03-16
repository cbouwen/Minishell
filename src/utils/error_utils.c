

#include "../../inc/minishell.h"

extern t_err	g_err;

void	init_err(t_err *err)
{
	err->type = CD;
	err->err = 0;
}

int	ft_error(char *str)
{
	printf("%s", str);
	return (0);
}

/*
  The purpose of this function is to fill the t_err struct and return 1
  to signify that an error has occured to the executor.
  it should always return 1, the 0 is there just in case something fucks up.
*/
int assign_and_handle_error(t_err_type type, int err_no)
{
	g_err.type = type;
	g_err.err = err_no;

	/*if (g_err.type == CD)
		handle_cd_error();
	else if (g_err.type == EXPORT)
		handle_export_error();
	else if (g_err.type == UNSET)
		handle_unset_error();
	else if (g_err.type == ENV)
		handle_env_error();
	else if (g_err.type == ECHO)
		handle_env_error();
	else if (g_err.type == PWD)
		handle_env_error();
	else if (g_err.type == EXECVE)
		handle_execve_error();
	else
		return (0);*/
	return (1);
}