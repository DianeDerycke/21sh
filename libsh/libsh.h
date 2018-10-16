/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:50:43 by dideryck          #+#    #+#             */
/*   Updated: 2018/10/16 16:51:54 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSH_H
# define LIBSH_H

#include "../libft/libft.h"

char    **sh_strsplit(const char *s, int(*ft)(char));

#endif
