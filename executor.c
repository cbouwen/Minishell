



int execute_command(   )
{



}



void find_arguments(t_token *token)
{
	while (token->type == ARG)
		token = token->right;
}


void	execute_token(t_token *token)
{
	int	fd;

	if (token->left)
		execute_token(token->left);
	if (token->type == COMMAND)
		token->input = execute_command(token, find_arguments(token))
	if (token->type == REDIRECT)
		execute_redirect(token->input, token->next->output);
	if (token->right != NULL)
		execute_token(token);
}

