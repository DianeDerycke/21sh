/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_whitespaces.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:52:38 by DERYCKE           #+#    #+#             */
/*   Updated: 2018/09/24 20:10:06 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_replace_whitespaces(char *str, char c)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (ft_is_whitespace(str[i]))
			str[i] = c;
		i++;
	}
}
