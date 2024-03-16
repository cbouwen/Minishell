

#include "../../inc/minishell.h"

void	init_err(t_err *err)
{
	err->type = CD;
	err->err = 0;
}