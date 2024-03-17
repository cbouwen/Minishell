

#include "../../inc/minishell.h"

extern int	g_err;

int	ft_error(char *str, int errno)
{
	g_err = errno;
	if (errno >= 133)
		printf("minishell: %s\n", strerror(errno));
	if (str)
		printf("%s", str);
	return (1);
}