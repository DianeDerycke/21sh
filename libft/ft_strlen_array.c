/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 01:09:16 by dideryck          #+#    #+#             */
/*   Updated: 2018/08/23 00:30:54 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen_array(char **tab)
{
	size_t		i;

	i = 0;
	if (!tab || !(*tab))
		return (0);
	while (tab[i])
		i++;
	return (i);
}
