/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:19:14 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/17 16:52:41 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

void	sh_display_prompt(t_env *env)
{
	char	*pwd;
	char	*home;

	pwd = sh_getvalue(env, "PWD");
	home = sh_getvalue(env, "HOME");
	if (!pwd)
		ft_putstr(PROMPT);
	else
	{
		ft_putstr(GREEN);
		ft_putstr(pwd);
		ft_putstr(RESET);
		ft_putchar(' ');
		ft_putstr(PROMPT);
	}
}
