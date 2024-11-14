/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:33:53 by noldiane          #+#    #+#             */
/*   Updated: 2023/11/23 11:02:19 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	c = (char)c;
	while (str[i] != '\0' || (c == '\0' && str[i] == '\0'))
	{
		if (str[i] == c)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
