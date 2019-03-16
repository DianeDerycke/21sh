/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 13:34:39 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/16 14:41:02 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char	**sh_get_env(void)
{
	extern char		**environ;
	char			**new_env;

	new_env = NULL;
	if (environ && environ[0] &&
		!(new_env = ft_copy_array(environ, ft_strlen_array(environ))))
		sh_malloc_error();
	return (new_env);
}
