/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:15:42 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/16 14:42:03 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char	*sh_strinsert(char *dst, char *src, int pos)
{
	char	*tmp;
	int		i;

	if (!dst || !src)
		return (NULL);
	i = 0;
	if (!(tmp = ft_strdup(&dst[pos])))
		return (NULL);
	while (src[i])
		dst[pos++] = src[i++];
	i = 0;
	while (tmp[i])
		dst[pos++] = tmp[i++];
	dst[pos] = '\0';
	ft_strdel(&tmp);
	return (dst);
}
