/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:17:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/08 00:53:23 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static int     is_valid_pipe(char *str)
{
    int     i;

    i = 0;
    while (str[i])
    {
        while (str[i] && ft_is_whitespace(str[i]))
            i++;
        if (str[i] == '|')
        {
            if (!str[i + 1])
                return (DQUOTE);
            while (str[i] && ft_is_whitespace(str[i]))
                i++;
            if (!str[i])
                return (DQUOTE);
        }
        i++;
    }
    return (SUCCESS);
}

void		handle_quotes(char **input)
{
	char	*tmp;
	int		ret;

	tmp = NULL;
	ret = 0;
	while (!tmp && (ret = is_valid_quotes(*input) || (ret = is_valid_pipe(*input))))
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
                    return (DQUOTE);
                i++;
                if (!str[i])
                    return (DQUOTE);
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
                return (SQUOTE);
        }
        i++;
    }
    if (j % 2 > 0)
        return (DQUOTE);
    return (SUCCESS);
}
//to do : valid quote should return size_t
