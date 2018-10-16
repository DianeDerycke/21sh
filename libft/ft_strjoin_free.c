/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 21:08:04 by DERYCKE           #+#    #+#             */
/*   Updated: 2018/10/02 15:52:01 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
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
	ft_strdel(&s1);
	return (str);
}
