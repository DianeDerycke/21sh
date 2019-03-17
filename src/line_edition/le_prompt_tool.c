/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_prompt_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:51:27 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/17 12:53:11 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

void	le_prompt_print(struct s_le *le_struct)
{
	if (le_struct->prompt_type == SUCCESS || le_struct->prompt_type == FAILURE)
	{
		ft_putstr(LE_PROMPT_BOLD);
		ft_putstr(le_struct->prompt_color);
		ft_putstr(le_struct->prompt);
		if (!ft_strcmp(le_struct->prompt_color, RED))
			ft_putstr(GREEN);
		if (le_struct->prompt_type == SUCCESS)
			ft_putstr(" > ");
		else
			ft_putstr(LE_FAILURE_CLR" > ");
		ft_putstr(LE_TERM_OFF);
	}
	else
		ft_putstr(le_struct->prompt);
}

/*
**	Print the prompt with colors, Print the prompt with colors
**	if the last command was succesful print the '>' in green else with red
*/

int		le_prompt_get_color(struct s_le *le_struct, char **env)
{
	int		fd;
	char	*path;
	char	*line;
	size_t	pos;

	path = NULL;
	line = NULL;
	if (!env || sh_find_variable("HOME", env, &pos) == -1)
		return (LE_FAILURE);
	if (!(path = sh_get_var_value(env[pos])))
		return (LE_FAILURE);
	if (!(path = ft_strjoin_free(path, LE_SHRC)))
		return ((int)sh_strmdel_return(path, NULL, NULL, (void *)LE_FAILURE));
	if ((fd = open(path, O_RDONLY)) == -1)
		return ((int)sh_strmdel_return(path, NULL, NULL, (void *)LE_FAILURE));
	ft_strdel(&path);
	if (get_next_line(fd, &line) == -1)
	{
		close(fd);
		return (LE_FAILURE);
	}
	close(fd);
	return (le_prompt_check_color(le_struct, line));
}

int		le_prompt_check_color(struct s_le *le_struct, char *line)
{
	ft_bzero(le_struct->prompt_color, 16);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "white"))
		ft_strcpy(le_struct->prompt_color, WHITE);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "red"))
		ft_strcpy(le_struct->prompt_color, RED);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "green"))
		ft_strcpy(le_struct->prompt_color, GREEN);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "yellow"))
		ft_strcpy(le_struct->prompt_color, YELLOW);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "blue"))
		ft_strcpy(le_struct->prompt_color, BLUE);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "magenta"))
		ft_strcpy(le_struct->prompt_color, MAGENTA);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "cyan"))
		ft_strcpy(le_struct->prompt_color, CYAN);
	ft_strdel(&line);
	if (le_struct->prompt_color[0])
		return (LE_SUCCESS);
	return (LE_FAILURE);
}
