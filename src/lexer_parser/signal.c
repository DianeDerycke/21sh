/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:28:25 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/28 20:30:15 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		kill(sig, get_pid(-1));
		ft_putstr_fd("21sh: Interrupt program. Signal received: ", 2);
		ft_putnbr_fd(sig, 2);
		ft_putendl_fd("", 2);
	}
}

pid_t	get_pid(pid_t val)
{
	static int 		pid;
	if (val != -1)
		pid = val;
	return (pid);
}