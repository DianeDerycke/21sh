/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_termcap_tool.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 17:37:26 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/21 15:32:50 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_termcap_print(char *str, int nb)
{
	char	*termc;
	int		i;

	i = 0;
	termc = tgetstr(str, NULL);
	if (!termc)
		return (LE_FAILURE);
	while (i < nb)
	{
		if (tputs(termc, 1, le_rputchar))
			return (LE_FAILURE);
		i++;
	}
	return (LE_SUCCESS);
}

/*
**	Print a termcap
*/

int		le_ansi_print(int nb, char *s)
{
	if (!s)
		return (LE_FAILURE);
	ft_putstr(LE_ESCAPEBRK);
	if (nb)
		ft_putnbr(nb);
	ft_putstr(s);
	return (LE_SUCCESS);
}

/*
**	Print a termcap in ansi format (ex: /033[12D), useful for print many termcap
*/

int		le_termcap_init(void)
{
	char	*term;

	term = getenv("TERM");
	if (!term)
		term = LE_TERM;
	if (tgetent(NULL, term) != 1)
		return (LE_FAILURE);
	return (LE_SUCCESS);
}

/*
**	Looks up the termcap entry for TERM
*/

int		le_rputchar(int c)
{
	if (!c)
		return (-LE_FAILURE);
	ft_putchar(c);
	return (c);
}

/*
**	Just char print with int return for tputs function
*/
