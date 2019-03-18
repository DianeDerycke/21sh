/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:22:13 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/18 16:08:40 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "../libsh/libsh.h"

typedef enum	e_err
{
	UNEXPTOKEN = 5,
	UNDEFVAR,
	CNOTFOUND,
	PERMDENIED,
	UNEXPEOF,
	NOFILEDIR,
	ERRFORK,
	ERRPIPE,
	NOTERM,
	ERRSIZE
}				t_err;

int			unexpected_eof(void);
int			get_error(int error_nb, char *str);
ssize_t		too_many_args(char *cmd);
void		error_option(char c);
int			syntax_error(char *str);
ssize_t		unvalid_setenv_cmd(void);
ssize_t		error_chdir(int error, char *path, char *cmd);
int			ambiguous_redirect(char *arg);

#endif
