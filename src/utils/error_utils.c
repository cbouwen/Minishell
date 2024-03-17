

#include "../../inc/minishell.h"

extern int	g_err;

int	ft_error(char *str, int err_no)
{
	g_err = errno;
	if (errno >= 133)
		printf("minishell: %s\n", strerror(err_no));
	if (str)
		printf("%s", str);
	return (1);
}