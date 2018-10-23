/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_add_field_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:31:51 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/23 16:45:04 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char	**sh_add_field_array(char **tab, char *newfield)
{
	char	**new;
	int		len;

	len = (ft_strlen_array(tab)) + 1;
	if (!(new = ft_copy_array(tab, len)))
		ft_malloc_error(SH21);
	ft_free_array(tab);
	if (!(new[len - 1] = ft_strdup(newfield)))
		ft_malloc_error(SH21);
	return (new);
}
