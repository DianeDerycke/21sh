/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:27:08 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/11 14:08:55 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "sh21.h"

int		hy_history_fill_list(struct s_le *le_struct);
int		hy_history_write(char *command);
void	hy_dlst_push(t_dlist **history, char *content);
void	hy_dlst_free(t_dlist *dlist);

#endif
