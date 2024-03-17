/*header pls*/

#include "../../inc/minishell.h"

int	pwd(t_token *token)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putstr_fd(cwd, token->output);
	ft_putchar_fd('\n', token->output);
	free(cwd);
	return (ft_error(NULL, 0));
}
