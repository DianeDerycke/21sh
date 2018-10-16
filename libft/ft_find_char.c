/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 14:52:40 by DERYCKE           #+#    #+#             */
/*   Updated: 2018/09/24 20:12:29 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t		ft_find_char(char *str, char c, size_t *index)
{
	*index = 0;
	if (!str)
		return (-1);
	while (str[*index] && str[*index] != c)
		(*index)++;
	if (!(str[*index]))
	{
		*index = 0;
		return (-1);
	}
	return (0);
}
