/*header pls*/

#include "../../inc/minishell.h"

void	print_env(t_token *tokens, t_environment *env)
{
	t_token			*temp;
	t_environment	*temp_env;

	temp = tokens;
	temp_env = env;
	while (temp_env)
	{
		ft_putstr_fd(temp_env->name, temp->output);
		ft_putchar_fd('=', temp->output);
		ft_putstr_fd(temp_env->value, temp->output);
		ft_putchar_fd('\n', temp->output);
		temp_env = temp_env->next;
	}
}
