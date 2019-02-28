/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:27:08 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/28 13:12:32 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "sh21.h"

# define HY_FILE	"/.21sh_history"

int		hy_history(struct s_le *le_struct, char **env);
int		hy_history_fill_list(struct s_le *le_struct, int fd, int ret);
int		hy_history_write(char *command, char **env);
void	hy_dlst_push(t_dlist **history, char *content);
void	hy_dlst_free(t_dlist *dlist);

#endif
