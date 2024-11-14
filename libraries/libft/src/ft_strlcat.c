/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:35:38 by noldiane          #+#    #+#             */
/*   Updated: 2023/11/10 16:36:05 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dest, const char *src, size_t destSize)
{
	size_t	index;
	size_t	src_len;
	size_t	dest_len;

	index = 0;
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (dest_len < destSize - 1 && destSize > 0)
	{
		while (src[index] && (dest_len + index) < (destSize - 1))
		{
			dest[dest_len + index] = src[index];
			index++;
		}
		dest[dest_len + index] = '\0';
	}
	if (dest_len >= destSize)
	{
		return (src_len + destSize);
	}
	return (dest_len + src_len);
}
