/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:05:44 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/17 03:16:10 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "../libsh/libsh.h"
# include "lineedition.h"
# include "error.h"
# include "lexer_parser.h"
# include "history.h"
# include "builtins.h"
# include "operators.h"
# include "execution.h"
# include "process_cmd.h"

//signal.h
void	signal_handler(int sig);
pid_t	get_pid(pid_t val);
int     handle_signal_pipe_edition(char *buffer);
int     handle_signal_quote_edition(char *buffer);

#endif
