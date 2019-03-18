/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 02:41:17 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/18 16:06:43 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_CMD_H
# define PROCESS_CMD_H
# include "../libsh/libsh.h"

typedef struct		s_expansion
{
	char	*tmp;
	char	*sub;
	char	*join;
	char	*v_value;
	int		index;
}					t_expansion;

int					handle_quotes(char **input);
int					is_valid_quotes(char *str);

ssize_t				apply_expansions(t_sh *shell, t_ast *ast);

#endif
