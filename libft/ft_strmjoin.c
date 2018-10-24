/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 17:15:16 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/03 17:30:50 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmjoin(char const *s1, char const *s2, char const *s3)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	if (!s1 || !s2 || !s3)
		return (NULL);
	size = ft_strlen(s1);
	if (!(str = ft_strnew(size + ft_strlen(s2) + ft_strlen(s3) + 1)))
		return (NULL);
	ft_strcpy(str, s1);
	while (s2[i])
		str[size++] = s2[i++];
	i = 0;
	while (s3[i])
		str[size++] = s3[i++];
	str[size] = '\0';
	return (str);
}
