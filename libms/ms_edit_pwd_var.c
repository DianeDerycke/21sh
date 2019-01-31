/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_edit_pwd_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 12:33:58 by dideryck          #+#    #+#             */
/*   Updated: 2018/09/25 14:38:57 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

ssize_t		ms_edit_pwd_var(char ***ms_env)
{
	char	*buf;
	size_t	index;

	index = 0;
	buf = NULL;
	if (ms_get_cwd(&buf) || ms_find_variable("PWD", *ms_env, &index) == -1)
		return (FAILURE);
	ms_edit_var("PWD", buf, ms_env, index);
	ft_strdel(&buf);
	return (SUCCESS);
}
