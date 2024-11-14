/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolan <nolan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:31:27 by noldiane          #+#    #+#             */
/*   Updated: 2024/05/28 15:20:55 by nolan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	count_size(char const *s, char c)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			size++;
		}
		i++;
	}
	return (size);
}

void	make_tab(char const *s, char c, char *ptr)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		ptr[i] = s [i];
		i++;
	}
	ptr[i] = '\0';
}

void	free_tabs(char **tab, int index)
{
	int	i;

	i = 0;
	while (i != index - 1)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

int	set_tab(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	count;
	size_t	index;

	i = 0;
	index = 0;
	while (s[index])
	{
		count = 0;
		while (s[index + count] && s[index + count] != c)
			count++;
		if (count > 0)
		{
			tab[i] = malloc(sizeof(char) * (count + 1));
			if (!tab[i])
				return (i);
			make_tab((s + index), c, tab[i]);
			i++;
			index = index + count;
		}
		else
			index++;
	}
	tab[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		result;
	char	**tab;
	size_t	size;

	size = count_size(s, c);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
	{
		free(tab);
		return (NULL);
	}
	result = set_tab(s, c, tab);
	if (result > 0)
		free_tabs(tab, result);
	return (tab);
}
