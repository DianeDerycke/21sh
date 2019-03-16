/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_too_few_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:28:38 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/16 14:42:06 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

ssize_t		sh_too_few_args(char *utility)
{
	ft_putstr_fd(utility, 2);
	ft_putendl_fd(": Too few arguments.", 2);
	return (FAILURE);
}
