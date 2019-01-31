/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clean_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:20:38 by DERYCKE           #+#    #+#             */
/*   Updated: 2018/09/24 17:44:05 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	**ms_clean_input(char **input)
{
	char		**tmp;

	tmp = NULL;
	if (!input || !*input)
		return (NULL);
	ft_replace(*input, C_DQUOTE, C_WHITESPACE);
	ft_replace_whitespaces(*input, C_WHITESPACE);
	if (!(tmp = ft_strsplit(*input, C_WHITESPACE)))
	{
		ft_strdel(input);
		return (NULL);
	}
	ft_strdel(input);
	return (tmp);
}
