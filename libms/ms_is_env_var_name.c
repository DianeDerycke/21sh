/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_env_var_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 20:07:26 by DERYCKE           #+#    #+#             */
/*   Updated: 2018/10/02 17:21:34 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

int		ms_is_env_var_name(char *str)
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
