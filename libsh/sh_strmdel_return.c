/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_strmdel_return.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:57:25 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/16 15:58:50 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

void	*sh_strmdel_return(char *s1, char *s2, char *s3, void *status)
{
	if (s1)
		ft_strdel(&s1);
	if (s2)
		ft_strdel(&s2);
	if (s3)
		ft_strdel(&s3);
	return (status);
}
