/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_cursor_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 15:54:51 by mrandou           #+#    #+#             */
/*   Updated: 2019/01/27 17:19:13 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_cursor_calcul_empty_area(struct s_le *le_struct)
{
	int	i;
	int	j;
	int	line;
	int	rest;
	int real;

	line = 0;
	rest =	0;
	if (!(le_struct->empty_area = (int *)malloc(sizeof(int *))))
		return (LE_FAILURE);
	i = 0;
	j = 0;
	while (le_struct->buff[i])
	{
		if (le_struct->buff[i] == '\n')
		{ 
			real = i + le_struct->prompt_size + le_struct->nb_empty_char;
			line = (real / le_struct->w_col) + 1;
			rest = (le_struct->w_col * line) - real;
			while (j <= rest)
				if (!(le_struct->empty_area = le_tab_add_value(\
				le_struct->empty_area, real + j++)))
					return (LE_FAILURE);
			le_struct->nb_empty_char += rest;
			j = 0;
		}
		i++;
	}
	return (LE_SUCCESS);
}

int		*le_tab_add_value(int *tab_old, int value)
{
	int *tab_new;
	int	nb_field;
	int	i;

	nb_field = 0;
	i = 0;
	while (tab_old[nb_field])
		nb_field++;
	tab_new = (int *)malloc(sizeof(int *) * (nb_field + 1));
	while (i < nb_field)
	{
		tab_new[i] = tab_old[i];
		i++;
	}
	free(tab);
	tab_new[i] = value;
	tab_new[i + 1] = 0;
	return (tab_new);
}
