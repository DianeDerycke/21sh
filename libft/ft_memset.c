/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 00:39:35 by DERYCKE           #+#    #+#             */
/*   Updated: 2017/11/30 02:53:48 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char*)b;
	i = 0;
	if (len == 0)
		return (b);
	while (i < len)
	{
		tmp[i] = ((unsigned char)c);
		i++;
	}
	return (b);
}
