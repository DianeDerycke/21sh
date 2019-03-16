/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_no_such_file_or_dir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 01:23:11 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/16 14:41:39 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

ssize_t		sh_no_such_file_or_dir(char *utility, char *cmd)
{
	ft_putstr_fd(utility, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (FAILURE);
}
