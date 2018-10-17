/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:45:14 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/17 14:58:43 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	read_loop(env_fill_list(env));
	return (0);
}
