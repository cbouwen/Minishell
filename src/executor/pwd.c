/*header pls*/

#include "../../inc/minishell.h"

int	pwd(t_token *token)
{
	char	*cwd;

	(void)token;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_error("pwd: error retrieving current directory\n", 1));
	printf("%s\n", cwd);
	/*ft_putstr_fd(cwd, token->output);
	ft_putchar_fd('\n', token->output);*/
	free(cwd);
	return (ft_error(NULL, 0));
}
