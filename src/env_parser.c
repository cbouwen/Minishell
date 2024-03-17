/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:27:38 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/13 16:25:25 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_lstadd_back_ms(t_environment **lst, t_environment *new)
{
	t_environment	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

t_environment	*create_node(char *name, char *value)
{
	t_environment	*new;

	new = (t_environment *)malloc(sizeof(t_environment));
	if (!new)
		ft_error(NULL, 12);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!new->name)
	{
		free_env(new);
		return (NULL);
	}
	return (new);
}

t_environment	*extract_data(char *envp)
{
	t_environment	*new;
	char			*name;
	char			*value;
	int				i;

	value = ft_strchr(envp, '=');
	if (!value)
		return (NULL);
	i = value - envp;
	value++;
	name = ft_substr(envp, 0, i);
	new = create_node(name, value);
	free(name);
	return (new);
}

t_environment	*env_parser(char *envp[])
{
	int				i;
	t_environment	*environment;

	i = 0;
	environment = NULL;
	while (envp[i])
	{
		ft_lstadd_back_ms(&environment, extract_data(envp[i]));
		i++;
	}
	return (environment);
}
