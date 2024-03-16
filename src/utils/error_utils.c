

#include "../../inc/minishell.h"

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