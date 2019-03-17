/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:17:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 18:00:56 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static int		only_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '|')
		i++;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (!str[i])
		return (SUCCESS);
	return (FAILURE);
}

static int		is_valid_pipe(char *str)
{
	int	i;

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

int				handle_quotes(char **input)
{
	char	*tmp;
	int		ret;

	tmp = NULL;
	ret = 0;
	while (!tmp && ((ret = is_valid_quotes(*input))
	|| (ret = is_valid_pipe(*input))))
	{
		if (!(tmp = line_edition(ret, NULL)))
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

int				is_valid_quotes(char *str)
{
	int		i;
	int		in_quote;
	int		in_squote;

	i = -1;
	in_quote = 0;
	in_squote = 0;
	if (!str)
		return (ERROR);
	while (str[++i])
	{
		if (str[i] == DQUOTE && in_quote != 0)
			in_quote--;
		else if (str[i] == DQUOTE && !in_quote)
			in_quote++;
		if (str[i] == SQUOTE && in_squote)
			in_squote--;
		else if (str[i] == SQUOTE && (!in_quote))
			in_squote++;
	}
	if (in_quote)
		return (DQUOTE);
	if (in_squote)
		return (SQUOTE);
	return (SUCCESS);
}

int				get_valid_input(t_param *param, char **env, int ret)
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
		if (handle_quotes(&param->input) == ERROR)
			return (FAILURE);
		if (param->input)
			break ;
	}
	return (SUCCESS);
}
