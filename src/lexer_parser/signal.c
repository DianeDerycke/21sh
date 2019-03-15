/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:28:25 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/15 14:58:12 by dideryck         ###   ########.fr       */
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

int     handle_signal_pipe_edition(char *buffer)
{
    if (buffer && ((ft_strcmp(buffer, "\004") == 0) || ft_strcmp(buffer, "\003") == 0))
    {
        if (ft_strcmp(buffer, "\004") == 0)
            get_error(UNEXPEOF, buffer);
        return (SUCCESS);
    }
    return (FAILURE);
}

int     handle_signal_quote_edition(char *buffer)
{
    if (buffer && ((ft_strcmp(buffer, "\n\004") == 0) || ft_strcmp(buffer, "\n\003") == 0))
    {
        if (ft_strcmp(buffer, "\n\004") == 0)
            get_error(UNEXPEOF, buffer);
        return (SUCCESS);
    }
    return (FAILURE);
}