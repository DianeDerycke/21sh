/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:02:38 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/18 14:50:58 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

ssize_t		has_echo_opt(char **split_cmd, size_t *index)
{
	ssize_t		is_opt;

	is_opt = 0;
	while (split_cmd[*index] && ((ft_strcmp(split_cmd[*index], "-n") == 0)))
	{
		is_opt++;
		(*index)++;
	}
	return (is_opt);
}

void		display_echo_arg(char **split_cmd, size_t index)
{
	while (split_cmd[index])
	{
		ft_putstr(split_cmd[index]);
		split_cmd[index + 1] ? ft_putchar(' ') : 0;
		index++;
	}
}

ssize_t		ms_echo(char **split_cmd, char ***ms_env, int ret)
{
	size_t		i;
	ssize_t		is_opt;

	(void)ms_env;
	(void)ret;
	i = 1;
	is_opt = has_echo_opt(split_cmd, &i);
	display_echo_arg(split_cmd, i);
	if (!(is_opt))
		ft_putchar('\n');
	return (SUCCESS);
}

ssize_t		ms_exit(char **split_cmd, char ***ms_env, int ret)
{
	(void)ms_env;
	(void)split_cmd;
	exit(ret);
}
