/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_is_env_var_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 20:07:26 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/16 14:41:31 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

int		sh_is_env_var_name(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_' && str[i] != '/'
				&& str[i] != ':' && str[i] != 92 && str[i] != '.' &&
				str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
