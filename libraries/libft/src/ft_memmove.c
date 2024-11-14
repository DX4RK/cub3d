/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:59:42 by noldiane          #+#    #+#             */
/*   Updated: 2023/11/10 15:59:43 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	counter;

	if (dest > src)
	{
		counter = (int)n - 1;
		while (counter >= 0)
		{
			*(char *)(dest + counter) = *(char *)(src + counter);
			counter--;
		}
	}
	else
	{
		counter = 0;
		while (counter < (int)n)
		{
			*(char *)(dest + counter) = *(char *)(src + counter);
			counter++;
		}
	}
	return (dest);
}
