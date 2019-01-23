/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 15:47:16 by dideryck          #+#    #+#             */
/*   Updated: 2019/01/23 17:00:22 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		create_line(char **rest, char **line)
{
	char	*tmp;
	int		j;

	tmp = NULL;
	j = 0;
	while ((*rest)[j] && (*rest)[j] != '\n')
		j++;
	*line = ft_strndup(*rest, j);
	if ((*rest)[j] && (*rest)[j] == '\n')
		j++;
	if ((*rest)[j])
	{
		tmp = ft_strdup(*rest + j);
		ft_strdel(rest);
		*rest = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else
	{
		ft_strdel(rest);
		*rest = ft_strdup("");
	}
}

static void		add_buffer_to_rest(char **rest, char buffer[], int ret)
{
	buffer[ret] = '\0';
	if (!(*rest))
		*rest = ft_strdup(buffer);
	else
		*rest = ft_strjoin_free(*rest, buffer);
}

int				get_next_line(const int fd, char **line)
{
	static t_pos		pos;

	pos.ret = 0;
	if (BUFF_SIZE <= 0 || fd < 0 || !line || read(fd, pos.buffer, 0) < 0)
		return (-1);
	if (!(pos.fd))
		pos.fd = fd;
	if (pos.fd != fd)
	{
		ft_strdel(&(pos.rest));
		pos.fd = fd;
	}
	while ((pos.ret = read(fd, pos.buffer, BUFF_SIZE)))
	{
		add_buffer_to_rest(&(pos.rest), pos.buffer, pos.ret);
		if (pos.rest && ft_strchr(pos.rest, '\n'))
			break ;
	}
	if (pos.ret < BUFF_SIZE && !(ft_strlen(pos.rest)))
		return (0);
	create_line(&(pos.rest), line);
	return (1);
}
