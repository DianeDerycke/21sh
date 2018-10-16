/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvisible.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 11:55:13 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/16 16:38:42 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_isvisible(char *str)
{
	size_t i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (ft_isprint(str[i]) && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
