/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:45:14 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/16 15:48:32 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	ft_putnbr(ft_isvisible(" "));

	return (0);
}