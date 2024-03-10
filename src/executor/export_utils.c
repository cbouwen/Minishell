/*header pls*/

#include "../../inc/minishell.h"

int	extract_name(char *token_str, char **var_name)
{
	int		sign_loc;
	char	*value;

	sign_loc = 0;
	value = NULL;
	value = ft_strchr(token_str, '=');
	if (!value)
		return (1);
	sign_loc = value - token_str;
	*var_name = ft_substr(token_str, 0, sign_loc);
	return (0);
}

int	extract_value(char *token_str, char **var_value)
{
	*var_value = ft_strdup(token_str);
	return (0);
}

int	check_env_val_exists(t_environment *env, char *var_name)
{
	while (env)
	{
		if (ft_strcmp(var_name, env->name) == 0)
			return (0);
		else
			env = env->next;
	}
	return (1);
}