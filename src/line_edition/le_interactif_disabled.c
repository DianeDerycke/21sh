/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_interactif_disabled.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 16:18:07 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/16 16:20:29 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

char	*le_interactif_disabled(void)
{
	char	*command;
	char	*line;
	int		ret;

	ret = 1;
	line = NULL;
	command = NULL;
	while (ret)
	{
		if ((ret = get_next_line(0, &line)) == -1)
			return (NULL);
		if (!ret && !line)
			break ;
		if (!(line = le_interactif_disabled_quote(line, &ret)))
			return (command);
		if (!(command = le_interactif_disabled_command(command, line)))
			return (NULL);
		ft_strdel(&line);
	}
	return (command);
}

char	*le_interactif_disabled_quote(char *line, int *ret)
{
	char	*tmp;
	int		valid;

	tmp = NULL;
	while ((valid = is_valid_quotes(line)))
	{
		if (valid == -1)
			return (sh_strmdel_return(line, NULL, NULL, NULL));
		if ((*ret = get_next_line(0, &tmp)) == -1)
			return (sh_strmdel_return(line, NULL, NULL, NULL));
		if (!ret && !tmp)
			break ;
		if (!(line = ft_strjoin_free(line, "\n")))
			return (sh_strmdel_return(line, tmp, NULL, NULL));
		if (!(line = ft_strjoin_free(line, tmp)))
			return (sh_strmdel_return(line, tmp, NULL, NULL));
		ft_strdel(&tmp);
	}
	return (line);
}

char	*le_interactif_disabled_command(char *command, char *line)
{
	if (line && !command)
	{
		if (!(command = ft_strdup(line)))
			return (sh_strmdel_return(line, NULL, NULL, NULL));
	}
	else if (line)
	{
		if (!(command = ft_strjoin_free(command, " ; ")))
			return (sh_strmdel_return(command, line, NULL, NULL));
		if (!(command = ft_strjoin_free(command, line)))
			return (sh_strmdel_return(command, line, NULL, NULL));
	}
	return (command);
}
