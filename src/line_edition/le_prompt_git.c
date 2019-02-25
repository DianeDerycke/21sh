/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_prompt_git.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:44:55 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/25 11:13:42 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_prompt_git(struct s_le *le_struct)
{
	char	*tmp;
	int		i;
	int		slash;

	i = 0;
	le_struct->git = NULL;
	if (!(tmp = le_prompt_git_read()))
		return (LE_FAILURE);
	while (tmp[i])
		if (tmp[i++] == '/')
			slash = i - 1;
	if (slash)
		le_struct->git = ft_strdup(tmp + slash + 1);
	else
		le_struct->git = ft_strndup(tmp, 7);
	if (!le_struct->git)
	{
		ft_strdel(&tmp);
		return (LE_FAILURE);
	}
	le_struct->prompt_size += ft_strlen(le_struct->git) + 2;
	ft_strdel(&tmp);
	return (LE_SUCCESS);
}

/*
**	Get the current branch of git
*/

char	*le_prompt_git_read(void)
{
	int		fd;
	char	*line;

	line = NULL;
	if ((fd = open(".git/HEAD", O_RDONLY)) == -1)
		return (NULL);
	if (get_next_line(fd, &line) == -1)
		return (NULL);
	return (line);
}

/*
**	Read the git file content the informations for the current path
*/

void	le_prompt_git_print(struct s_le *le_struct)
{
	if (!le_struct->git)
		return ;
	ft_putstr(LE_GIT_CLR"(");
	ft_putstr(le_struct->git);
	ft_putstr(")"LE_TERM_OFF);
}

/*
**	Print the git branch on the prompt
**	if the current path are a repertory of git
*/
