/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 17:09:02 by dideryck          #+#    #+#             */
/*   Updated: 2018/08/23 14:57:16 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	int		start;
	int		end;
	int		len;
	char	*cpy;

	cpy = 0;
	start = 0;
	if (!s)
		return (NULL);
	end = ft_strlen(s) - 1;
	while (start < end && ft_is_whitespace(s[start]))
		start++;
	while (end > 0 && ft_is_whitespace(s[end]))
		end--;
	if (start >= end)
		return (ft_strdup(""));
	len = end - start + 1;
	if (!(cpy = (char *)malloc(len + 1)))
		return (NULL);
	cpy[len] = '\0';
	ft_memcpy(cpy, s + start, len);
	return (cpy);
}
