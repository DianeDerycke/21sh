/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:00:37 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/18 15:25:24 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/operators.h"

t_pid		*get_pid_list(t_pid *new_list)
{
	static t_pid *pid_list = NULL;

	if (new_list)
		pid_list = new_list;
	return (pid_list);
}

void		close_pipe(int *fd)
{
	if (!fd)
		return ;
	close(fd[INPUT_END]);
	close(fd[OUTPUT_END]);
}

void		close_dup(int *fd, int std)
{
	if (!fd)
		return ;
	close(fd[std == STDIN_FILENO ? INPUT_END : OUTPUT_END]);
	dup2(fd[std == STDIN_FILENO ? OUTPUT_END : INPUT_END], std);
	close(fd[std == STDIN_FILENO ? OUTPUT_END : INPUT_END]);
}
