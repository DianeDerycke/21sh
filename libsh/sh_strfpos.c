/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_strfpos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:55:22 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/17 12:17:40 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

int	sh_strfpos(char *str, char oc)
{
	int i;

	i = 0;
	if ((!str) || (!oc))
		return (0);
	while (str[i])
		if (str[i++] == oc)
			return (i);
	return (0);
}
