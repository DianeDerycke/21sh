/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 16:42:46 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/17 14:58:56 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

t_list	*read_input(void)
{
	t_list	*list;
	char	buff[4096];
	int		i;

	list = NULL;
	i = 0;
	ft_strclr(buff);
	while (buff[i - 1] != 10)
		if (read(STDIN_FILENO, &buff[i++], 1) == -1)
			return (NULL);
	buff[i] = '\0';
	if (!(list = ft_lstnew(buff, ft_strlen(buff) - 1)))
		return (NULL);
	return (list);
}

void	read_loop(t_env *env)
{
	t_list	*list;
	t_list	*historic;
	int		i;

	(void)env;
	i = 0;
	list = NULL;
	historic = NULL;
	while (42)
	{
		ft_putstr(PROMPT);
		if (!(list = read_input()))
			return ;
		ft_lstadd(&historic, list);
		ft_putendl("");
		i = 0;
	}
}
