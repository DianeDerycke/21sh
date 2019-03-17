/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 02:41:17 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 02:42:28 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_CMD
#define PROCESS_CMD
#include "../libsh/libsh.h"

typedef struct		s_expansion
{
	char	*tmp;
	char	*sub;
	char	*join;
	char	*v_value;
	int		index;
}					t_expansion;


//QUOTES
int			handle_quotes(char **input);
int     	is_valid_quotes(char *str);
//EXPANSIONS
ssize_t		apply_expansions(t_sh *shell, t_ast *ast);

#endif