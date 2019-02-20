/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:17:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/20 15:37:05 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

void		handle_quotes(char **input)
{
	char	*tmp;
	int		ret;

	tmp = NULL;
	ret = 0;
	while (!tmp && (ret = is_valid_quotes(*input)))
	{
		if (!(tmp = line_edition(ret , NULL))) //to edit when feature \n line edition is add : if ft_strcmp(\n, tmp)
			continue;
		*input = ft_strjoin_free(*input, tmp);
		ft_strdel(&tmp);
	}
}

int     is_valid_quotes(char *str)
{
    int     i;
    int     len;
    int     j;

    i = 0;
    len = ft_strlen(str);
    j = 0;
    if (!str)
        return (-1);
    while (str[i])
    {
        if (str[i] == DQUOTE)
        {
            i++;
            j++;
            while (str[i] && str[i] != DQUOTE)
            {
                if (str[i] && str[i] == BACKSLASH && str[i + 1])
                    i++;
                else if (!str[i + 1])
                    return (2);
                i++;
                if (!str[i])
                    return (2);
            }
            if (str[i] == DQUOTE)
                j++;
        }
        if (str[i] == SQUOTE)
        {
			j = 0;
			i++;
            while (str[i] && str[i] != SQUOTE)
                i++;
            if (!str[i] || str[i] != SQUOTE)
                return (1);
        }
        i++;
    }
    if (j % 2 > 0)
        return (2);
    return (SUCCESS);
}
//to do : valid quote should return size_t
