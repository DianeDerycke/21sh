/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:45:14 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/17 16:24:41 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_env 	*l_env;
	char	buff[BUFF_SIZE];

	l_env = env_fill_list(env);
	while (42)
	{
		sh_display_prompt(env);
		read_input(buff);
	}
	return (SUCCESS);
}
