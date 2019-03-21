/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:28:25 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/21 17:46:44 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		is_signal(1);
		ft_putstr_fd("21sh: Interrupt program. Signal received: ", 2);
		ft_putnbr_fd(sig, 2);
		ft_putendl_fd("", 2);
	}
}

void	kill_all_process(t_pid *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		kill(lst->proc, SIGINT);
		lst = lst->next;
	}
}

int		signal_pipe(pid_t child_pid, t_sh *shell)
{
	sh_push_pidnew(child_pid, &(shell->l_pid));
	get_pid_list(shell->l_pid);
	signal(SIGINT, signal_handler);
	if (is_signal(0) == 1)
		return (1);
	return (0);
}
