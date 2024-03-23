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
	while (temp->type != PIPE)
	{
		if (temp->type == REDIRECT && temp_args->redirect != HERE_DOC)
		{
			if (!temp->next)
				return (3);
			if (temp->next->type == ARG)
			{
				args->file = ft_strdup(temp->next->str);
				return (0);
			}
		}
		else if (temp->type == REDIRECT && temp_args->redirect == HERE_DOC)
			heredoc_setup(temp, args);
		temp = temp->next;
	}
	return (1);
}

int	heredoc_setup(t_token *token, t_args *args)
{
	/*int		fd;
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
	return (0);*/
	t_token	*temp;
	t_args	*temp_args;

	temp = token;
	temp_args = args;
	if (!temp->next || temp->next->type != ARG)
		temp_args->file = ft_strdup("heredoc");
	else
		temp_args->file = ft_strdup(temp->next->str);
	return (0);
}
