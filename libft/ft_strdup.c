/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 22:30:13 by DERYCKE           #+#    #+#             */
/*   Updated: 2018/06/15 13:52:27 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*cpy;

	len = 0;
	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	cpy = (char *)malloc((len + 1) * (sizeof(char)));
	if (cpy == NULL)
		return (NULL);
	while (i < len && s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
