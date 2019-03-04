/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:28:25 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/04 15:53:52 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

void	signal_handler(int sig)
{
	t_pid	*pid_list;
	if (sig == SIGINT)
	{
		pid_list = get_pid_list(NULL);
		while (pid_list)
		{
			kill(pid_list->proc, sig);
			pid_list = pid_list->next;
		}
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