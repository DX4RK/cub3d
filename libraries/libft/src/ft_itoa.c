/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:37:21 by noldiane          #+#    #+#             */
/*   Updated: 2023/11/23 13:51:34 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	count_digit(int n)
{
	int				count;
	unsigned int	num;

	count = 0;
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
		num = (unsigned int) -n;
	else
		num = n;
	while (num != 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

void	set(char *ptr, unsigned int n, int is_neg, int len)
{
	int	i;

	i = len - 1;
	ptr[len] = '\0';
	if (is_neg)
		ptr[0] = '-';
	while (i >= is_neg)
	{
		ptr[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	char			*ptr;
	int				len;
	unsigned int	num;

	num = n;
	len = count_digit(n);
	if (n < 0)
	{
		len += 1;
		num = (unsigned int) -n;
	}
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	set(ptr, num, n < 0, len);
	return (ptr);
}
