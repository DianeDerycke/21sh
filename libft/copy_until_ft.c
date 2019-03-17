/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_until_ft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 15:48:24 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/17 16:36:09 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*copy_until_ft(char *s, int *start, int (*f)(int c))
{
	char	*tmp;
	int		length;

	tmp = NULL;
	length = 0;
	while (s[length] && f(s[length]) == 1)
		length++;
	if (!(tmp = ft_strndup(s, length)))
		return (NULL);
	*start += length;
	return (tmp);
}
