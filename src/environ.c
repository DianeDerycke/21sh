/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:07:36 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/23 18:05:56 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

t_env		*env_fill_list(char **env)
{
	t_env	*environ_struct;
	t_env 	*head;
	int		i;
	int		oc;

	i = 0;
	oc = 0;
	if (!env || !env[0])
		return (NULL);
	environ_struct = sh_create_elem();
	head = environ_struct;
	while (env[i])
	{
		if (!(oc = sh_strfpos(env[i], C_EQUAL)))
			return (NULL);
		if (!(environ_struct->key = ft_strndup(env[i], oc - 1)))
			ft_malloc_error(SH21);
		if (!(environ_struct->value = ft_strdup(env[i] + oc)))
			ft_malloc_error(SH21);
		environ_struct->next = sh_create_elem();
		environ_struct = environ_struct->next;
		i++;
	}
	return (head);
}

void		env_display(t_env *env)
{
	while (env->next)
	{
		ft_putstr(BLUE);
		ft_putstr(env->key);
		ft_putstr(WHITE);
		ft_putchar('=');
		ft_putstr(RED);
		ft_putendl(env->value);
		ft_putstr(RESET);
		env = env->next;
	}
}
