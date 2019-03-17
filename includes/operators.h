/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 02:30:42 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 18:25:43 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
#define OPERATORS_H
#include "../libsh/libsh.h"

#define INPUT_END 1
#define OUTPUT_END 0
#define PERM 0677

//PIPE
int 		do_pipe(t_sh *shell, t_ast *ast);

//PIPE_UTILS
t_pid 	    *get_pid_list(t_pid *new_list);
void		close_pipe(int *fd);
void		close_dup(int *fd, int std);

//REDIR_FUNCTIONS
int 		handle_agregation(t_ast *redir, t_ast *ast);
//REDIR
int    		*getter_std(int init);
void    	reset_std(int *fd);
int    		exec_redirection(t_ast *ast, t_sh *shell);

//HEREDOC
int     	handle_heredoc(t_ast *redir);
char    	*prompt_heredoc(char *end_word);
int     	find_heredoc(t_ast *ast);

//REDIR UTILS
t_ast  		*find_next_redir(t_ast *ast);
t_ast    	*add_argument_to_cmd(t_ast *ast);
int     	get_str_redir(t_ope token);

#endif