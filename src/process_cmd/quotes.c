/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:17:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 15:39:46 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

//NORME 1 FT

static int      only_pipe(char *str)
{
    int     i;

    i = 0;
    while (str[i] && ft_is_whitespace(str[i]))
        i++;
    if (str[i] == '|')
        i++;
    while(str[i] && ft_is_whitespace(str[i]))
        i++;
    if (!str[i])
        return (SUCCESS);
    return (FAILURE);
}

static int     is_valid_pipe(char *str)
{
    int     i;

    i = 0;
    if (only_pipe(str) == SUCCESS)
        return (SUCCESS);
    while (str[i])
    {
        while (str[i] && ft_is_whitespace(str[i]))
            i++;
        if (str[i] == '|')
        {
            if (!str[i + 1])
                return (IS_PIPE);
            i++;
            while (str[i] && ft_is_whitespace(str[i]))
                i++;
            if (!str[i])
                return (IS_PIPE);
        }
        i++;
    }
    return (SUCCESS);
}

int 		handle_quotes(char **input)
{
	char	*tmp;
	int		ret;

	tmp = NULL;
	ret = 0;
	while (!tmp && ((ret = is_valid_quotes(*input)) || (ret = is_valid_pipe(*input))))
	{
		if (!(tmp = line_edition(ret , NULL)))
			continue;
        if (tmp && (handle_signal_pipe_edition(tmp) == SUCCESS 
            || handle_signal_quote_edition(tmp) == SUCCESS))
        {
            ft_strdel(&tmp);
            ft_strdel(input);
            return (FAILURE);
        }
		*input = ft_strjoin_free(*input, tmp);
		ft_strdel(&tmp);
	}
    return (SUCCESS);
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
        if (str[i] == DQUOTE && str[i + 1])
        {
            i++;
            j++;
            while (str[i] && str[i] != DQUOTE)
                i++;
            if (str[i] == DQUOTE)
                j++;
        }
        else if (str[i] == DQUOTE && !str[i + 1])
            return (DQUOTE);
        else
        {
            i++;
            continue;
        }
        if (str[i] == SQUOTE && str[i + 1])
        {
			j = 0;
			i++;
            while (str[i] && str[i] != SQUOTE)
                i++;
            if (!str[i] || str[i] != SQUOTE)
                return (SQUOTE);
        }
        else if (str[i] == SQUOTE)
            return (SQUOTE);
        i++;
    }
    if (j % 2 > 0)
        return (DQUOTE);
    return (SUCCESS);
}

int     get_valid_input(t_param *param, char **env, int ret)
{
	if (LE_BUFF_SIZE <= 0)
	{
		if (!(param->input = ft_strdup("exit")))
			sh_malloc_error();
		get_error(ERRSIZE, "21sh: Unvalid buffer size.");
		return (SUCCESS);
	}
	while (21)
	{
		if (!(param->input = line_edition(ret, env)))
		{
			ret = SUCCESS;
			continue;
		}
		if (handle_quotes(&param->input) == FAILURE)
            return (FAILURE);
		if (param->input)
			break ;
	}
	return (SUCCESS);
}
