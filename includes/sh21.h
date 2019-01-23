/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:05:44 by dideryck          #+#    #+#             */
/*   Updated: 2019/01/23 17:16:09 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "../libft/libft.h"
# include "../libsh/libsh.h"
# include "lexer.h"
# include "lineedition.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

void	read_input(char buff[]);

t_env	*env_fill_list(char **env);
void	env_display(t_env *env);

#endif
