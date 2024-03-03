/*header pls*/

#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "minishell.h"

void	echo(t_token *tokens);
void	echo_no_arg(t_token *tokens);
void	pwd(t_token *token);
void	start(t_token *tokens);

#endif