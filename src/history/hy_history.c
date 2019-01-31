/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hy_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 11:42:59 by mrandou           #+#    #+#             */
/*   Updated: 2019/01/31 10:39:00 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"


void	hy_dlst_push(t_dlist **history, char *content)
{
	t_dlist *newlist;

	if (!(newlist = (t_dlist *)malloc(sizeof(t_dlist))))
		return ;
	if (!(newlist->content = ft_strdup(content)))
		return ;
	newlist->next = *history;
	newlist->prev = NULL;
	if (*history)
		(*history)->prev = newlist;
	*history = newlist;
}

void	hy_dlst_free(t_dlist *dlist)
{
	t_dlist	*tmp;

	tmp = NULL;
	while (dlist)
	{
		tmp = dlist->next;
		if (dlist->content)
			free(dlist->content);
		free(dlist);
		dlist = tmp;
	}
}

int		hy_history_fill_list(struct s_le *le_struct)
{
	int		fd;
	int		ret;
	char	*line;
	char	*tmp;

	ret = 1;
	line = NULL;
	tmp = NULL;
	if (!le_struct)
		return (FAILURE);
	le_struct->history = NULL;
	if ((fd = open(".21sh_history", O_RDONLY | O_CREAT, S_IRWXU)) == -1)
		return (FAILURE);
	while (ret != -1 && ret)
	{
		if ((ret = get_next_line(fd, &line)) == -1)
			return (FAILURE);
		while (ret != -1 && ret && valid_quotes(line))
		{
			if ((ret = get_next_line(fd, &tmp)) == -1)
				return (FAILURE);
			if (!ret)
			{
				ft_strdel(&line);
				return (LE_SUCCESS);
			}
			if (!(line = ft_strjoin(line, tmp)))
				return (FAILURE);
			ft_strdel(&tmp);
		}
		hy_dlst_push(&le_struct->history, line);
		ft_strdel(&line);
	}
	if (close(fd) == -1)
		return (FAILURE);
	return (SUCCESS);
}

int		hy_history_write(char *command)
{
	int	fd;

	if ((fd = open(".21sh_history", O_WRONLY | O_APPEND)) == -1)
		return (1);
	if ((write(fd, command, ft_strlen(command))) == -1)
	{
		close(fd);
		return (1);
	}
	if ((write(fd, "\n", 1)) == -1)
	{
		close(fd);
		return (1);
	}
	if (close(fd) == -1)
		return (1);
	return (0);
}
