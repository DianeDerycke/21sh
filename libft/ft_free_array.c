/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 02:35:04 by dideryck          #+#    #+#             */
/*   Updated: 2018/09/19 17:54:57 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char **tab)
{
	int		i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while (tab[i])
	{
		ft_memdel((void *)&tab[i]);
		i++;
	}
	ft_memdel((void *)tab[i]);
	ft_memdel((void *)&tab);
}
