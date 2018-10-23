/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_remove_field_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 17:46:17 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/23 18:06:07 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

void	sh_remove_field_array(char **tab, int field)
{
	int	i;

	i = 0;
	if (!tab || !tab[0] || field < 0 || field > (int)ft_strlen_array(tab))
		return ;
	if (tab[field][0] && tab[field])
		ft_strdel(&tab[field]);
	while (tab[field + 1])
	{
		tab[field] = tab[field + 1];
		field++;
	}
	tab[field] = NULL;	
}
