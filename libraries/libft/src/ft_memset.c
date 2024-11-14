/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:15:06 by noldiane          #+#    #+#             */
/*   Updated: 2023/11/10 14:18:32 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memset(void *str, int rp, size_t n)
{
	size_t	counter;

	counter = 0;
	while (counter != n)
	{
		*(unsigned char *)(str + counter) = (unsigned char)rp;
		counter++;
	}
	return (str);
}
