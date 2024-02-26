#include "../../inc/minishell.h"

void    parse_pipes(t_token *tmp, t_token **head)
{
    t_token    *tmp_head;

    *head = NULL;
    tmp_head = NULL;
    while (tmp)
    {
        if (tmp->type == PIPE)
        {
            if (tmp_head)
            {
                tmp->left = tmp_head;
                tmp_head->parent = tmp;
            }
            tmp_head = tmp;
        }
        tmp = tmp->next;
    }
}