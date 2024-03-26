/*header pls*/

#include "../../../inc/minishell.h"

int	setup_heredoc(t_token *tokens, t_environment *env, t_args *args)
{
	t_token			*temp;
	t_args			*temp_args;
	t_environment	*tem_env;

	temp = tokens;
	temp_args = args;
	tem_env = env;
	(void)tem_env;
	while (temp && temp->type != REDIRECT)
		temp = temp->next;
	if (!temp->next || temp->next->type != ARG)
		return (ft_error("heredoc: syntax error 1\n", 3));
	else
	{
		if (temp->next->next && temp->next->next->type == ARG)
			return (ft_error("heredoc: syntax error 2\n", 3));
		else
			args->delimiter = ft_strdup(temp->next->str);
	}
	temp = temp->next;
	if (!temp->next || temp->next->type != REDIRECT)
		return (ft_error(NULL, heredoc_no_redirect(temp_args)));
	else
		return (ft_error(NULL, heredoc_redirect(temp->next, temp_args)));
}

/*jump to next token*/
/*temp = temp->next->next;
if (temp->type != REDIRECT || ft_strcmp(temp->str, "<<") == 0)
	return (ft_error("heredoc: syntax error 2\n", 3));
else
	determine_redirect(temp, temp_args);
temp = temp->next;
if (temp->type != ARG)
	return (ft_error("heredoc: syntax error 3\n", 3));
else
	args->file = ft_strdup(temp->str);
check_file_exists(temp_args);
return (0);*/

int execute_heredoc(t_token *tokens, t_environment *env, t_args *args)
{
	t_token			*temp;
	t_environment	*temp_env;
	t_args			*temp_args;

	temp = tokens;
	temp_env = env;
	temp_args = args;
	if (temp_args->heredoc_fd == -1)
	{
		if (execute_heredoc_nord(temp, temp_env, temp_args) != 0)
			return (ft_error("heredoc: heredoc_no_redirect error\n", 3));
	}
	else
	{
		if (execute_heredoc_rd(temp, temp_env, temp_args) != 0)
			return (ft_error("heredoc: execute_heredoc_nord error\n", 3));
	}
	return (ft_error(NULL, 0));
}

int	heredoc_no_redirect(t_args *args)
{
	char	*line;

	args->file = ft_strdup("/tmp/heredoc_dump");
	args->fd = open(args->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (args->fd == -1)
		return (ft_error("heredoc_no_redirect: open error\n", 3));
	line = readline("heredoc> ");
	while (ft_strcmp(line, args->delimiter) != 0)
	{
		write(args->fd, line, ft_strlen(line));
		write(args->fd, "\n", 1);
		free(line);
		line = NULL;
		line = readline("heredoc> ");
	}
	close(args->fd);
	if (line)
		free(line);
	return (0);
}

int	update_args(t_args *args, char *path)
{
	int		len;
	int		i;
	char	**temp;

	len = 0;
	while (args->arg_array[len])
		len++;
	temp = malloc(sizeof(char *) * (len + 2));
	if (!temp)
		return (ft_error("update_args: malloc error\n", 12));
	i = 0;
	while (i < len)
	{
		temp[i] = ft_strdup(args->arg_array[i]);
		if (!temp[i])
			return (ft_error("update_args: strdup error\n", 12));
		i++;
	}
	temp[i] = ft_strdup(path);
	if (!temp[i])
		return (ft_error("update_args: strdup error\n", 12));
	temp[i + 1] = NULL;
	free_array(args->arg_array);
	args->arg_array = temp;
	return (0);
}

int execute_heredoc_nord(t_token *tokens, t_environment *env, t_args *args)
{
	args->redirect = INPUT;
	if (open_file(args) != 0)
		return (ft_error("execute_heredoc: open_file error\n", 3));
	if (redirect_input(tokens, env, args) != 0)
		return (ft_error("execute_heredoc: redirect_input error\n", 3));
	return (ft_error(NULL, 0));
}

int	heredoc_redirect(t_token *tokens, t_args *args)
{
	t_token			*temp;
	t_args			*temp_args;


	temp = tokens;
	temp_args = args;
	if (determine_redirect(temp, args) != 0)
		return (ft_error("heredoc_redirect: determine_redirect error\n", 3));
	if (!temp->next || temp->next->type != ARG)
		return (ft_error("heredoc: syntax error 3\n", 3));
	temp = temp->next;
	args->file = ft_strdup(temp->str);
	if (!args->file)
		return (ft_error("heredoc: strdup error\n", 12));
	if (open_heredoc_rd(temp_args) != 0)
		return (ft_error("heredoc: open_heredoc_rd error\n", 3));
    return (0);
}

int	open_heredoc_rd(t_args *args)
{
	char	*line;

	args->hd_file = ft_strdup("/tmp/heredoc_dump");
	args->heredoc_fd = open(args->hd_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (args->heredoc_fd == -1)
		return (ft_error("heredoc_no_redirect: open error\n", 3));
	line = readline("heredoc> ");
	while (ft_strcmp(line, args->delimiter) != 0)
	{
		write(args->heredoc_fd, line, ft_strlen(line));
		write(args->heredoc_fd, "\n", 1);
		free(line);
		line = NULL;
		line = readline("heredoc> ");
	}
	close(args->heredoc_fd);
	if (line)
		free(line);
	return (0);
}

/*int				saved_stdin;
	t_token			*temp;
	t_environment	*temp_env;
	t_args			*temp_args;

	temp = tokens;
	temp_env = env;
	temp_args = args;
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return ;
	if (dup2(temp_args->fd, STDIN_FILENO) == -1)
		return ;
	close(temp_args->fd);
	prep_cmd(temp, temp_env, temp_args);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		return ;
	close(saved_stdin);*/
	/*t_token			*temp;
	t_environment	*temp_env;
	t_args			*temp_args;
	int				saved_stdin;
	//int				status;

	temp = tokens;
	temp_env = env;
	temp_args = args;
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return ;
	if (dup2(temp_args->fd, STDIN_FILENO) == -1)
		return ;
	close(temp_args->fd);
	prep_cmd(temp, temp_env, temp_args);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		return ;
	close(saved_stdin);
	//return (ft_error(NULL, status));*/