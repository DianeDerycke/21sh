/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 16:42:46 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/17 17:00:03 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	read_input(char buff[])
{
	int		i;

	i = 0;
	ft_strclr(buff);
	while (buff[i - 1] != '\n')
	{
		if (read(STDIN_FILENO, &buff[i++], 1) == -1)
			return ;
	}
}
