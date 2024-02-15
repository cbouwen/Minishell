/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:46:39 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/15 12:52:56 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	counter(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strndup(const char *s, size_t j)
{
	char		*t;
	size_t		len;
	size_t		i;

	i = 0;
	len = counter(s);
	t = malloc(sizeof(char) * (len + 1));
	if (!t)
		return (NULL);
	while (s[i] && i < j)
	{
		t[i] = s[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
