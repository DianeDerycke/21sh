/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:08:35 by dderycke          #+#    #+#             */
/*   Updated: 2017/11/30 00:49:56 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int		i;
	int		n;

	i = 0;
	if (little[0] == '\0')
		return ((char*)big);
	n = ft_strlen(little);
	while (big[i] != '\0')
	{
		if (ft_strncmp(little, big + i, n) == 0)
			return (((char *)big) + i);
		i++;
	}
	return (NULL);
}
