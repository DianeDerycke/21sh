/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 13:34:39 by DERYCKE           #+#    #+#             */
/*   Updated: 2018/10/03 17:55:44 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	**ms_get_env(void)
{
	extern char		**environ;
	char			**new_env;

	new_env = NULL;
	if (environ && environ[0] &&
		!(new_env = ft_copy_array(environ, ft_strlen_array(environ))))
		ms_malloc_error();
	return (new_env);
}
