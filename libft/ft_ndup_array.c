/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ndup_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:56:33 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/19 15:42:48 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_ndup_array(char *v1, char *v2, char *v3, int size_array)
{
	char	**array;

	if (!v1 || !v2 || !v3 || size_array <= 0)
		return (NULL);
	if (!(array = ft_memalloc(sizeof(char *) * size_array)))
		return (NULL);
	array[0] = ft_strdup(v1);
	array[1] = ft_strdup(v2);
	array[2] = ft_strdup(v3);
	array[3] = NULL;
	return (array);
}
