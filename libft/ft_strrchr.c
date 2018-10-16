/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:18:38 by dideryck          #+#    #+#             */
/*   Updated: 2017/11/30 00:49:53 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] == ((char)c))
			i = j;
		j++;
	}
	if (s[j] == '\0' && c == '\0')
		return ((char*)(s + j));
	if (i == 0 && s[i] != ((char)c))
		return (NULL);
	return ((char*)(s + i));
}
