/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:05:44 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/21 18:03:47 by dideryck         ###   ########.fr       */
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

t_sh	*init_shell(void);

/*
** signal.h
*/
int		is_signal(int val);
void	kill_all_process(t_pid *lst);
void	signal_handler(int sig);
pid_t	get_pid(pid_t val);
int		handle_signal_pipe_edition(char *buffer);
int		handle_signal_quote_edition(char *buffer);
int		signal_pipe(pid_t child_pid, t_sh *shell);

#endif
