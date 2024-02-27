#include "../../inc/minishell.h"

/*void    parse_no_pipe(t_token *tmp, t_token **tmp_head)
{


}

void    parse_pipe(t_token *token, t_token **tmp_head, int pipes)
{
    t_token *tmp;

    tmp = token;
    token = tmp_head;
    while (tmp->left || pipes != 0)
        token = token->left;
    while (tmp)
    {
        if (tmp->type == REDIRECT)
            token->left = tmp;
        tmp = tmp->next;
    }
    
    
  }

void    parse_redirects(t_token *tmp, t_token **tmp_head, int pipes)
{
    if (tmp_head)
        parse_pipe(tmp, tmp_head, pipes);
    else
        parse_no_pipe(tmp, tmp_head);

}*/

t_token redirect_left(t_token *tmp)
{
    t_token *token;

    token = tmp;
    while (tmp->left)
        tmp = tmp->left;
}

void    parse_redirects(t_token *tmp, t_token **tmp_head, int pipes)
{
    int pipe_counter;

    pipe_counter = pipes;
    while (tmp)
    {
        if (tmp->type == REDIRECT && pipe_counter == pipes)
            tmp->parent = redirect_left(tmp);
        else if (tmp->type == REDIRECT)
            tmp->parent = redirect_right(tmp);
        if (tmp->type == PIPE)
            pipe_counter--;
        tmp = tmp->next;
    }
}
