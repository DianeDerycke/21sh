/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_too_few_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:28:38 by dideryck          #+#    #+#             */
/*   Updated: 2018/09/24 19:40:38 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

ssize_t		ms_too_few_args(char *utility)
{
	ft_putstr_fd(utility, 2);
	ft_putendl_fd(": Too few arguments.", 2);
	return (FAILURE);
}
