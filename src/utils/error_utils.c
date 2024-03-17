

#include "../../inc/minishell.h"

extern int	g_err;

int	ft_error(char *str, int err_no)
{
	g_err = err_no;
	if (err_no == 0)
		return (0);
	if (err_no <= 133)
		printf("%s\n", strerror(err_no));
	if (str)
		printf("%s", str);
	return (1);
}