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
		return (ft_error(NULL, heredoc_no_redirect(temp, temp_args)));
	else
		return (ft_error(NULL, heredoc_redirect(temp, temp_args)));
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

int	heredoc_no_redirect(t_token *tokens, t_args *args)
{
	char    *line;
	char	*path;

	(void)tokens;

	path = ft_strdup("/tmp/heredoc_dump");
	args->arg_array[1] = path;
    args->fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
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
    if (line)
        free(line);
	free(path);
    return (0);
}

void execute_command_with_heredoc(t_token *tokens, t_environment *env, t_args *args)
{
	int				saved_stdin;
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
	printf("args->args[0]: %s\n", temp_args->arg_array[0]);
	printf("args->args[1]: %s\n", temp_args->arg_array[1]);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		return ;
	close(saved_stdin);
	/*saved_stdin = dup(STDIN_FILENO);
    heredoc_no_redirect(tokens, args);

	prep_cmd(tokens, env, args);*/
}

int	heredoc_redirect(t_token *tokens, t_args *args)
{
	t_token	*temp;
	t_args	*temp_args;

	temp = tokens;
	temp_args = args;

	(void)temp;
	(void)temp_args;
	printf("heredoc_redirect\n");
	printf("delimiter: %s\n", args->delimiter);
	return (0);
}