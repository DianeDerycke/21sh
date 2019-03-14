/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_freesnd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:40:03 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/14 17:40:23 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

char	*ft_strjoin_freesnd(char *s1, char *s2)
{
	char			*str;

	str = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) *
		((ft_strlen(s1) + ft_strlen(s2) + 1)))))
		return (NULL);
	ft_bzero(str, ft_strlen(s1) + ft_strlen(s2) + 1);
	str = ft_strcat(str, s1);
	str = ft_strcat(str, s2);
	ft_strdel(&s2);
	return (str);
}
