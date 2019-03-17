/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 16:18:12 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 16:41:11 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 50000

# include "libft.h"
# include <fcntl.h>

typedef struct		s_pos
{
	int					fd;
	int					ret;
	char				buffer[BUFF_SIZE + 1];
	char				*rest;
}					t_pos;

int					get_next_line(const int fd, char **line);

#endif
