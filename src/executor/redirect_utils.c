/*header pls*/

#include "../../inc/minishell.h"

int	determine_redirect(t_token *tokens, t_args *args)
{
	t_token	*temp;
	t_args	*temp_args;

	temp = tokens;
	temp_args = args;
	while (temp->type != PIPE)
	{
		if (temp->type == REDIRECT)
		{
			if (ft_strcmp(temp->str, ">") == 0)
				temp_args->redirect = OUTPUT;
			else if (ft_strcmp(temp->str, ">>") == 0)
				temp_args->redirect = APPEND;
			else if (ft_strcmp(temp->str, "<") == 0)
				temp_args->redirect = INPUT;
			else if (ft_strcmp(temp->str, "<<") == 0)
				temp_args->redirect = HERE_DOC;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

int	determine_file(t_token *tokens, t_args *args)
{
	t_token	*temp;
	t_args	*temp_args;

	temp = tokens;
	temp_args = args;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIRECT && temp_args->redirect != HERE_DOC)
		{
			if (temp->next->type == ARG)
			{
				args->file = ft_strdup(temp->next->str);
				check_file_exists(temp_args);
				return (0);
			}
		}
		else if (temp->type == REDIRECT && temp_args->redirect == HERE_DOC)
		{
			setup_heredoc(temp, temp_args);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

void	check_file_exists(t_args *args)
{
	char	*path;
	char	*file_path;
	t_args	*temp_args;

	temp_args = args;
	path = getcwd(NULL, 0);
	file_path = ft_strjoin(path, "/");
	file_path = ft_strjoin_free(file_path, temp_args->file, true);
	free(temp_args->file);
	temp_args->file = ft_strdup(file_path);
	if (access(file_path, F_OK) == 0)
		temp_args->file_exists = 1;
	else
		temp_args->file_exists = 0;
	free(file_path);
	free(path);
	open_file(temp_args);
}

int open_file(t_args *args)
{
	int fd;

	if (args->redirect == OUTPUT)
		fd = open(args->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (args->redirect == APPEND)
		fd = open(args->file, O_RDWR | O_APPEND, 0644);
	else if (args->redirect == INPUT)
		fd = open(args->file, O_RDWR);
	else if (args->redirect == HERE_DOC)
	{
		if (args->heredoc_redirect == OUTPUT)
			fd = open(args->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (args->heredoc_redirect == APPEND)
			fd = open(args->file, O_RDWR | O_APPEND, 0644);
		else if (args->heredoc_redirect == INPUT)
			fd = open(args->file, O_RDWR);
	}
	if (fd < 0)
		return (ft_error("redirection: no such file or directory\n", 4));
	args->fd = fd;
	return (ft_error(NULL, 0));
}

int setup_heredoc(t_token *tokens, t_args *args)
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
		args->delimiter = ft_strdup(temp->next->str);
	temp = temp->next->next;

	printf("temp->str: %s\n", temp->str);

	if (temp->type != REDIRECT || ft_strcmp(temp->str, "<<") == 0)
		return (ft_error("heredoc: syntax error 2\n", 3));
	else
		temp_args->heredoc_redirect = ft_strdup(temp->str);
	temp = temp->next;
	if (temp->type != ARG)
		return (ft_error("heredoc: syntax error 3\n", 3));
	else
		args->file = ft_strdup(temp->next->str);
	open_file(temp_args);
	return (0);
}

/*int	heredoc_setup(t_token *token, t_args *args)
{
	int		fd;
	char	*line;

	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, token->next->str) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	args->file = ft_strdup("heredoc");
	return (0);
}*/
