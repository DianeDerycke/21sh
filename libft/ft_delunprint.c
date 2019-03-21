/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delunprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 16:36:28 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/21 16:36:44 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_delunprint(char *str, size_t n)
{
	char	*dst;

	dst = str;
	while (n--)
	{
		*str = *dst;
		if (ft_isprint(*str))
			str++;
		dst++;
	}
	ft_bzero(str, dst - str);
	return (dst - str);
}
