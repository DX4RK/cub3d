/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:50:12 by noldiane          #+#    #+#             */
/*   Updated: 2023/11/13 16:15:17 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *hy, const char *nd, size_t l)
{
	size_t	i;
	size_t	b;

	i = 0;
	b = 0;
	if (nd[0] == '\0')
		return ((char *)hy);
	while (i < l && hy[i] != '\0')
	{
		if (hy[i] == nd[0])
		{
			b = 0;
			while (nd[b] != '\0' && i + b < l && hy[i + b] == nd[b])
			{
				b++;
			}
			if (nd[b] == '\0')
			{
				return ((char *)&hy[i]);
			}
		}
		i++;
	}
	return (NULL);
}
