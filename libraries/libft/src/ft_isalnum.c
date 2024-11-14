/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:42:18 by noldiane          #+#    #+#             */
/*   Updated: 2023/11/23 10:26:22 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_isalnum(int cr)
{
	if (ft_isalpha(cr) > 0 || ft_isdigit(cr) > 0)
	{
		return (8);
	}
	return (0);
}
