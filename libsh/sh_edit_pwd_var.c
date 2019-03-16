/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_edit_pwd_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 12:33:58 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/16 14:40:24 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

ssize_t		sh_edit_pwd_var(char ***ms_env)
{
	char	*buf;
	size_t	index;

	index = 0;
	buf = NULL;
	if (sh_get_cwd(&buf) || sh_find_variable("PWD", *ms_env, &index) == -1)
		return (FAILURE);
	sh_edit_var("PWD", buf, ms_env, index);
	ft_strdel(&buf);
	return (SUCCESS);
}
