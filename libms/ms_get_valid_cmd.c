/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_valid_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 12:16:30 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/06 18:06:40 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static char		*ms_test_each_path(char **path_array, char *cmd)
{
	struct stat		buf;
	char			*filename;
	char			*tmp;
	int				i;

	tmp = NULL;
	filename = NULL;
	i = 0;
	while (path_array[i])
	{
		tmp = ft_strjoin(path_array[i], "/");
		filename = ft_strjoin_free(tmp, cmd);
		if (stat(filename, &buf) == 0 && (S_ISREG(buf.st_mode)))
		{
			ft_free_array(path_array);
			return (filename);
		}
		ft_strdel(&filename);
		i++;
	}
	ft_free_array(path_array);
	return (NULL);
}

char			*ms_get_valid_cmd(char *cmd, char **ms_env)
{
	struct stat		buf;
	char			*dir_path;
	char			**path_array;

	path_array = NULL;
	dir_path = NULL;
	if (!cmd)
		return (NULL);
	if (stat(cmd, &buf) == 0 && (S_ISREG(buf.st_mode) &&
			(buf.st_mode & S_IXUSR)))
		return (ft_strdup(cmd));
	if (!(dir_path = ms_find_path_variable(ms_env)))
		return (NULL);
	path_array = ft_strsplit(dir_path, ':');
	ft_strdel(&dir_path);
	if ((dir_path = ms_test_each_path(path_array, cmd)))
	{
		ft_free_array(path_array);
		free(path_array);
		return (dir_path);
	}
	ft_free_array(path_array);
	free(path_array);
	return (NULL);
}
