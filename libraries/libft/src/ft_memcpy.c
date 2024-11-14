/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:34:26 by noldiane          #+#    #+#             */
/*   Updated: 2023/11/10 15:59:01 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	counter;

	counter = 0;
	while (counter != n)
	{
		*(unsigned char *)(dest + counter) = *(unsigned char *)(src + counter);
		counter++;
	}
	return (dest);
}
