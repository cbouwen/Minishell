

#include "../../inc/minishell.h"

extern int	g_err;

int	ft_error(char *str)
{
	g_err = 1;
	if (str)
		printf("%s", str);
	return (1);
}