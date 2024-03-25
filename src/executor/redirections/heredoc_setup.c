/*header pls*/

#include "../../../inc/minishell.h"

int	setup_heredoc(t_token *tokens, t_args *args)
{
	t_token	*temp;
	t_args	*temp_args;

	temp = tokens;
	temp_args = args;

	/*jump to redirect*/
	while (temp && temp->type != REDIRECT)
		temp = temp->next;

	/*check if there is a delimiter*/
	if (!temp->next || temp->next->type != ARG)
		return (ft_error("heredoc: syntax error 1\n", 3));
	else
	{
		while (temp->next && temp->next->type == ARG)
		{
			if (temp->next->has_space)
				temp->next->str = strjoin_free(temp->next->str, " ", 0);
			if (args->delimiter)
				args->delimiter = strjoin_free(args->delimiter, temp->next->str, 1);
			else
				args->delimiter = ft_strdup(temp->next->str);
			temp = temp->next;
		}
	}

	/*check for new redirect*/
	if (!temp->next || temp->next->type != REDIRECT)
		heredoc_no_redirect(temp, temp_args);
	else
		heredoc_redirect(temp, temp_args);
	return (0);
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
}

int	heredoc_no_redirect(t_token *tokens, t_args *args)
{
	t_token	*temp;
	t_args	*temp_args;

	temp = tokens;
	temp_args = args;

	(void)temp;
	(void)temp_args;
	printf("heredoc_no_redirect\n");
	printf("delimiter: %s\n", args->delimiter);
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