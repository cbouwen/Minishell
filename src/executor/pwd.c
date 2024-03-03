/*header pls*/

#include "../../inc/minishell.h"

void	pwd(t_token *token)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return ;
	}
	ft_putstr_fd(cwd, token->output);
	ft_putchar_fd('\n', token->output);
	free(cwd);
}
