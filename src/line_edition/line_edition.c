/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 17:16:08 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/05 14:27:16 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

char	*line_edition(int prompt, char **env)
{
	struct termios	backup;
	struct s_le		le_struct;

	if (!isatty(0))
		return (le_interactif_disabled());
	le_struct.buff = NULL;
	le_struct.prompt_type = prompt;
	if (le_init_set_attribute(&backup))
		return (NULL);
	if (le_read_and_exec(&le_struct, env))
	{
		if (tcsetattr(STDIN_FILENO, 0, &backup))
			return (NULL);
		ft_strdel(&le_struct.buff);
		return (NULL);
	}
	if (tcsetattr(STDIN_FILENO, 0, &backup))
		return (NULL);
	if (!(le_struct.nb_char))
	{
		ft_strdel(&le_struct.buff);
		return (NULL);
	}
	return (le_struct.buff);
}

/*
**	le_ = line_edition
**	It's this function that will have to be called for line edition
**	Set the attribute for the shell and launch the read/execute function
*/


int		le_read_and_exec(struct s_le *le_struct, char **env)
{
	int	ret;

	if (le_init_struct(le_struct, env))
		return (LE_FAILURE);
	while (LE_INFINITE_LOOP)
	{
		if (le_window_check(le_struct))
			return (LE_FAILURE);
		if ((ret = le_init(le_struct, env)) != LE_CONTINUE)
			return (ret);
		if (read(STDIN_FILENO, le_struct->tmp, 1) == -1)
			return (LE_FAILURE);
		if (le_termcap_check(le_struct) != LE_FAILURE && le_struct->term)
			if (le_termcap_exec(le_struct))
				return (LE_FAILURE);
		if (!le_struct->term && ft_isprint(le_struct->tmp[0])\
		&& le_struct->nb_char < le_struct->max_size)
			if (le_buff_append(le_struct, le_struct->tmp[0]))
				return (LE_FAILURE);
	}
	return (LE_FAILURE);
}

/*
**	Initialize the shell, and read char by char the standard input
**	Check if it's  a termcaps, if it's true, then launch the termcap function
**	Else add the char to the buffer
*/

char	*le_interactif_disabled(void)
{
	char	*command;
	char	*line;
	int		ret;

	command = NULL;
	line = NULL;
	ret = 1;
	if ((ret = get_next_line(0, &command)) == -1)
		return (NULL);
	while (ret != -1 && ret && is_valid_quotes(command))
	{
		if ((ret = get_next_line(0, &line)) == -1)
		{
			ft_strdel(&command);
			return (NULL);
		}
		if (!(command = ft_strmjoin(command, "\n", line)))
		{
			ft_strdel(&line);
			ft_strdel(&command);
			return (NULL);
		}
		ft_strdel(&line);
	}
	while (ret != -1 && ret)
	{
		if (line)
		{
			if (!(command = ft_strmjoin(command, " ; ", line)))
			{
				ft_strdel(&line);
				ft_strdel(&command);
				return (NULL);
			}
			ft_strdel(&line);
		}
		if ((ret = get_next_line(0, &line)) == -1)
		{
			ft_strdel(&command);
			return (NULL);
		}
	}
	return (command);
}
