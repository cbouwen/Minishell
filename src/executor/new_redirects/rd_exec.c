/*header pls*/

#include "../../../inc/minishell.h"

int	rd_exec_setup(t_token *tok, t_environment *env, t_args *arg, t_rd_collection *rd)
{
	t_token			*temp;
	t_environment	*temp_env;
	t_args			*temp_args;
	t_rd_collection	*temp_rd;

	temp = tok;
	temp_env = env;
	temp_args = arg;
	temp_rd = rd;
	if (temp_rd->input_size > 0 && temp_rd->output_size == 0)
		input_rd(temp, temp_env, temp_args, temp_rd);
	else if (temp_rd->output_size > 0 && temp_rd->input_size == 0)
		output_rd(temp, temp_env, temp_args, temp_rd);
	else if (temp_rd->output_size > 0 && temp_rd->input_size > 0)
		//mega super cool redirection
		printf("mega super cool redirection\n");
	else
		//error?
		printf("error?\n");
	return (rd_error_handler(0, NULL, temp_rd));
}

int	input_rd(t_token *tok, t_environment *env, t_args *arg, t_rd_collection *rd)
{
	t_token			*temp;
	t_environment	*temp_env;
	t_args			*temp_args;
	t_rd_collection	*temp_rd;
	int				status;

	temp = tok;
	temp_env = env;
	temp_args = arg;
	temp_rd = rd;
	status = 0;
	temp_rd->stdin = dup(STDIN_FILENO);
	if (temp_rd->stdin == -1)
		return (rd_error_handler(3, NULL, rd));
	if (rd->input[rd->input_size - 1][0] == '#')
		rd->i_fd = open("/tmp/heredoc_dump", O_RDONLY);
	if (dup2(temp_rd->i_fd, STDIN_FILENO) == -1)
		return (rd_error_handler(4, NULL, temp_rd));
	close(temp_rd->i_fd);
	status = prep_cmd(temp, temp_env, temp_args);
	if (dup2(temp_rd->stdin, STDIN_FILENO) == -1)
		return (rd_error_handler(4, NULL, temp_rd));
	close(temp_rd->stdin);
	return (rd_error_handler(status, NULL, temp_rd));
}

int	output_rd(t_token *tok, t_environment *env, t_args *arg, t_rd_collection *rd)
{
	t_token			*temp;
	t_environment	*temp_env;
	t_args			*temp_args;
	t_rd_collection	*temp_rd;
	int				status;

	temp = tok;
	temp_env = env;
	temp_args = arg;
	temp_rd = rd;
	status = 0;
	temp_rd->stdout = dup(STDOUT_FILENO);
	if (temp_rd->stdout == -1)
		return (rd_error_handler(3, NULL, rd));
	if (rd->output[rd->output_size - 1][0] == '#')
		rd->o_fd = open("/tmp/heredoc_dump", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dup2(temp_rd->o_fd, STDOUT_FILENO) == -1)
		return (rd_error_handler(4, NULL, temp_rd));
	close(temp_rd->o_fd);
	status = prep_cmd(temp, temp_env, temp_args);
	if (dup2(temp_rd->stdout, STDOUT_FILENO) == -1)
		return (rd_error_handler(4, NULL, temp_rd));
	close(temp_rd->stdout);
	return (rd_error_handler(status, NULL, temp_rd));
}
