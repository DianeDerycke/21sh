/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_integer_table.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 00:28:33 by dideryck          #+#    #+#             */
/*   Updated: 2017/11/30 00:49:30 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_integer_table(int *tab, int size)
{
	int		n;
	int		tmp;

	n = 0;
	tmp = 0;
	while (n < size)
	{
		if (tab[n] > tab[n + 1] && n + 1 < size)
		{
			tmp = tab[n];
			tab[n] = tab[n + 1];
			tab[n + 1] = tmp;
		}
		++n;
	}
	n = 0;
	while (tab[n] <= tab[n + 1])
		n++;
	if (n < size - 1)
		ft_sort_integer_table(tab, size);
}
