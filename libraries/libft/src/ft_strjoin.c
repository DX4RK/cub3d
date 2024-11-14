/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:31:36 by noldiane          #+#    #+#             */
/*   Updated: 2023/11/17 10:13:29 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc(((s1_len + s2_len) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (i < s1_len && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len && s2[i])
	{
		ptr[s1_len + i] = s2[i];
		i++;
	}
	ptr[s1_len + i] = '\0';
	return (ptr);
}
