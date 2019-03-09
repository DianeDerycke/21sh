/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:17:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/09 16:07:53 by dideryck         ###   ########.fr       */
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

int     get_valid_input(t_param *param, char **env, int ret)
{
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

static int     handle_signal_pipe_edition(char *buffer)
{
    if (buffer && ((ft_strcmp(buffer, "\004") == 0) || ft_strcmp(buffer, "\003") == 0))
    {
        if (ft_strcmp(buffer, "\004") == 0)
            get_error(UNEXPEOF, buffer);
        return (SUCCESS);
    }
    return (FAILURE);
}

static int     handle_signal_quote_edition(char *buffer)
{
    if (buffer && ((ft_strcmp(buffer, "\n\004") == 0) || ft_strcmp(buffer, "\n\003") == 0))
    {
        if (ft_strcmp(buffer, "\n\004") == 0)
            get_error(UNEXPEOF, buffer);
        return (SUCCESS);
    }
    return (FAILURE);
}

int 		handle_quotes(char **input)
{
	char	*tmp;
	int		ret;

	tmp = NULL;
	ret = 0;
	while (!tmp && (((ret = is_valid_quotes(*input)) || (ret = is_valid_pipe(*input)))))
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
