/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:22:13 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 15:39:04 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
#define ERROR_H
#include "../libsh/libsh.h"

typedef enum    e_err 
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
}               t_err;

int 	    unexpected_eof(void);
int         get_error(int error_nb, char *str);
ssize_t		too_many_args(char *cmd);
void		error_option(char c);
int			syntax_error(char *str);
ssize_t		unvalid_setenv_cmd(void);
ssize_t		error_chdir(int error, char *path, char *cmd);
int			ambiguous_redirect(char *arg);

#endif
