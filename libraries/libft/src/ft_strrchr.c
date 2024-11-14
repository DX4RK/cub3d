/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:50:50 by noldiane          #+#    #+#             */
/*   Updated: 2023/11/23 11:03:35 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *str, int c)
{
	const char	*lst_ocu;

	lst_ocu = NULL;
	c = (char)c;
	while (*str != '\0')
	{
		if (*str == c)
		{
			lst_ocu = str;
		}
		str++;
	}
	if (c == '\0')
	{
		return ((char *)str);
	}
	return ((char *)lst_ocu);
}
