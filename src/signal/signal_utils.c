/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 17:11:00 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/21 17:21:56 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		is_signal(int val)
{
	static int		sig = 0;

	if (val > 0)
		sig = val;
	return (val);
}

pid_t	get_pid(pid_t val)
{
	static int	pid;

	if (val != -1)
		pid = val;
	return (pid);
}

int		handle_signal_pipe_edition(char *buffer)
{
	if (buffer && ((ft_strcmp(buffer, "\004") == 0) ||
	ft_strcmp(buffer, "\003") == 0))
	{
		if (ft_strcmp(buffer, "\004") == 0)
			get_error(UNEXPEOF, buffer);
		return (SUCCESS);
	}
	return (FAILURE);
}

int		handle_signal_quote_edition(char *buffer)
{
	if (buffer && ((ft_strcmp(buffer, "\n\004") == 0) ||
	ft_strcmp(buffer, "\n\003") == 0))
	{
		if (ft_strcmp(buffer, "\n\004") == 0)
			get_error(UNEXPEOF, buffer);
		return (SUCCESS);
	}
	return (FAILURE);
}
