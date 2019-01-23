
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 16:18:12 by DERYCKE           #+#    #+#             */
/*   Updated: 2018/04/13 15:40:05 by dideryck         ###   ########.fr       */
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
