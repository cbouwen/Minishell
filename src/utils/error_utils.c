

#include "../../inc/minishell.h"

extern t_signal	g_signal;

int	ft_error(char *str, int err_no)
{
	g_signal.err_no = err_no;
	if (g_signal.err_no == 0)
		return (0);
	if (str)
		printf("%s", str);
	return (err_no);
}
