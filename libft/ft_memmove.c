/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 22:37:19 by dideryck          #+#    #+#             */
/*   Updated: 2017/11/30 00:49:18 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	tmp1 = (unsigned char*)dst;
	tmp2 = (unsigned char*)src;
	if (src == dst)
		return (dst);
	if (src < dst)
	{
		tmp1 = tmp1 + (len - 1);
		tmp2 = tmp2 + (len - 1);
		while (len--)
			*tmp1-- = *tmp2--;
	}
	else
		while (len--)
			*tmp1++ = *tmp2++;
	return (dst);
}
