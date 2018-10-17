/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:19:14 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/17 17:16:41 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

void	sh_display_prompt(t_env *env)
{
	char	*pwd;
	char	*home;
	int		len;

	pwd = sh_getvalue(env, "PWD");
	home = sh_getvalue(env, "HOME");
	len = 0;
	if (!pwd)
		ft_putstr(PROMPT);
	else
	{
		if (home && !ft_strncmp(home, pwd, (len = ft_strlen(home))))
			ft_putmstr(GREEN, "~", pwd + len, RESET);
		else
			ft_putmstr(GREEN, pwd, RESET,  NULL);
		ft_putchar(' ');
		ft_putstr(PROMPT);
	}
}
