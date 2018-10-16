/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 21:37:50 by DERYCKE           #+#    #+#             */
/*   Updated: 2018/09/24 20:09:44 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_replace(char *str, char c, char new_c)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			str[i] = new_c;
		i++;
	}
}
