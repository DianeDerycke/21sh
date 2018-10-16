/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 12:04:49 by dideryck          #+#    #+#             */
/*   Updated: 2018/10/01 14:07:09 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_clear_screen(void)
{
	const char		*clear;

	clear = "\e[1;1H\e[2J";
	write(STDOUT_FILENO, clear, 12);
	write(STDOUT_FILENO, "\r", 1);
}
