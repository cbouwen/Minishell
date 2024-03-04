/*header pls*/

#include "../../inc/minishell.h"

void	print_env(t_token *tokens, t_environment *env)
{
	t_token			*temp;
	t_environment	*temp_env;

	temp = tokens;
	temp_env = env;
	if (temp->next && temp->next->type == ARG
		&& ft_strcmp(temp->next->str, "env") != 0)
	{
		env_error_msg(temp->next);
		return ;
	}
	while (temp_env)
	{
		ft_putstr_fd(temp_env->name, temp->output);
		ft_putchar_fd('=', temp->output);
		ft_putstr_fd(temp_env->value, temp->output);
		ft_putchar_fd('\n', temp->output);
		temp_env = temp_env->next;
	}
}

void	env_error_msg(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	ft_putstr_fd("env: '", 2);
	ft_putstr_fd(temp->str, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
}
