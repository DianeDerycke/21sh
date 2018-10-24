/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:00:16 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/24 16:28:53 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

void	sh_env_display(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (env[i])
	{
		tmp = sh_get_env_key(env, i);
		ft_putmstr(GREEN, tmp, D_GRAY, "=");
		ft_putstr(RESET);
		ft_putmstr(L_GRAY, sh_get_env_value(env, tmp), "\n", RESET);
		i++;
	}
}
