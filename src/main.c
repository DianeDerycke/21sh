/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:45:14 by mrandou           #+#    #+#             */
/*   Updated: 2018/11/07 13:59:16 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_env 	*l_env;
	char	**env_copy;
	char	buff[BUFF_SIZE];

	l_env = env_fill_list(env);
	if (!(env_copy = ft_copy_array(env, ft_strlen_array(env))))
		ft_malloc_error(SH21);
	sh_env_display(env_copy);
	ft_putendl(" ");
	while (42)
	{
		sh_display_prompt(l_env);
		read_input(buff);
	}
	return (SUCCESS);
}
