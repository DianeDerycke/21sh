/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 11:42:59 by mrandou           #+#    #+#             */
/*   Updated: 2019/01/23 13:43:47 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/lineedition.h"


void	dlst_push(t_dlist **history, char *content)
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

void	dlst_free(t_dlist *dlist)
{
	t_dlist	*tmp;

	tmp = NULL;
	while (dlist)
	{
		tmp = dlist;
		if (dlist->content)
			free(dlist->content);
		free(tmp);
		dlist = dlist->next;
	}
}

int		history_fill_list(struct s_le *le_struct)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	le_struct->history = NULL;
	if ((fd = open(".21sh_history", O_RDONLY | O_CREAT, S_IRWXU)) == -1)
		return (1);
	while (ret != -1 && ret)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (2);
		dlst_push(&le_struct->history, line);
		ft_strdel(&line);
	}
	if (close(fd) == -1)
		return (1);
	return (0);
}

int		history_write(char *command)
{
	int	fd;

	if ((fd = open(".21sh_history", O_WRONLY | O_APPEND)) == -1)
		return (1);
	if ((write(fd, command, ft_strlen(command))) == -1)
		return (1);
	if ((write(fd, "\n", 1)) == -1)
		return (1);
	if (close(fd) == -1)
		return (1);
	return (0);
}
