/*header pls*/

#include "../../../inc/minishell.h"

int	setup_heredoc(t_token *tokens, t_args *args)
{
	t_token	*temp;
	t_args	*temp_args;

	temp = tokens;
	temp_args = args;
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
	t_token	*temp;
	t_args	*temp_args;
	char	*path;

	temp = tokens;
	temp_args = args;

	(void)temp;
	(void)temp_args;

	path = ft_strdup("/tmp/heredoc_dump");
	if (!path)
		return (ft_error("heredoc_no_redirect: malloc error\n", 12));
	args->fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (args->fd == -1)
		return (ft_error("heredoc_no_redirect: open error\n", 3));
	while (line = readline("heredoc> "))
	{
		if (ft_strcmp(line, args->delimiter) == 0)
			free(line);
		write(args->fd, line, ft_strlen(line));
		write(args->fd, "\n", 1);
		free(line);
	}
	close(args->fd);
	free(path);
	return (0);
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