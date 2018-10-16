/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:50:43 by dideryck          #+#    #+#             */
/*   Updated: 2018/10/16 16:42:53 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LIBSH_H
# define LIBSH_H

#include <unistd.h>

char    **sh_strsplit(const char *s, int(*ft)(char));

#endif