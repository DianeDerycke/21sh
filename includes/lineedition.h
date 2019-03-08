/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineedition.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 17:14:24 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/08 12:29:51 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINEEDITION_H
# define LINEEDITION_H

# include "sh21.h"
# include <term.h>
# include <termios.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>

# define LE_SUCCESS			0
# define LE_FAILURE			1
# define LE_CONTINUE		2
# define LE_INFINITE_LOOP	21
# define LE_BUFF_SIZE		2048
# define LE_TMP_BUFF_SIZE	16
# define LE_PROMPT_CLR		"\033[1m\033[32m"
# define LE_FAILURE_CLR		"\033[1m\033[31m"
# define LE_GIT_CLR			"\033[1m\033[34m"
# define LE_PROMPT 			LE_PROMPT_CLR"$> \033[0m"
# define LE_PROMPT_DQUOTE	"\033[1m\033[30mdquote \\> \033[0m"
# define LE_PROMPT_SQUOTE	"\033[1m\033[30msquote \\> \033[0m"
# define LE_PROMPT_PIPE		"\033[1m\033[30mpipe |> \033[0m"
# define LE_PROMPT_SIMPLE	3
# define LE_PROMPT_DEF_SIZE	4
# define LE_PROMPT_QTE_SIZE	11
# define LE_ESCAPE			'\033'
# define LE_ESCAPEBRK		"\033["
# define LE_ENDL			'\n'
# define LE_EXIT 			'\003'
# define LE_EOT 			'\004'
# define LE_UP				"A"
# define LE_DOWN			"B"
# define LE_RIGHT			"C"
# define LE_LEFT			"D"
# define LE_MOVE			"G"
# define LE_START			-1
# define LE_TERM			"xterm-256color"
# define LE_CUT				21
# define LE_PASTE			16
# define LE_COPY			25
# define LE_CLEAR			12
# define LE_SELECT_ON		"\033[100m"
# define LE_TERM_OFF		"\033[0m"
# define LE_REALLOC			1

/*
**	Termcaps DEFINE
*/

# define TC_INSERT_ON		"im"
# define TC_INSERT_OFF		"ei"
# define TC_GET_COL			"co"
# define TC_GET_LINE		"li"
# define TC_GET_POS			"\033[6n"
# define TC_GO_LEFT			"le"
# define TC_GO_RIGHT		"nd"
# define TC_GO_UP			"up"
# define TC_GO_DOWN			"do"
# define TC_GO_BEGIN		"cr"
# define TC_CLEAR			"cl"
# define TC_CLEAR_NEXT		"cd"
# define TC_DELETE_CHAR		"dc"
# define TC_DELETE_LINE		"dl"
# define TC_SAVE_CPOS		"sc"
# define TC_RESTORE_CPOS	"rc"
# define TC_UP				"\033[A"
# define TC_DOWN			"\033[B"
# define TC_RIGHT			"\033[C"
# define TC_LEFT			"\033[D"
# define TC_DELFRONT		"\033[3~"
# define TC_END				"\033[F"
# define TC_HOME			"\033[H"
# define TC_SH_UP			"\033[1;2A"
# define TC_SH_DOWN			"\033[1;2B"
# define TC_SH_RIGHT		"\033[1;2C"
# define TC_SH_LEFT			"\033[1;2D"
# define TC_DEL				'\177'

typedef	enum		e_termnum
{
	LE_ARROW_UP = 2,
	LE_ARROW_DOWN,
	LE_ARROW_LEFT,
	LE_ARROW_RIGHT,
	LE_DELFRONT,
	LE_DEL,
	LE_SHIFT_RIGHT,
	LE_SHIFT_LEFT,
	LE_SHIFT_UP,
	LE_SHIFT_DOWN,
	LE_END,
	LE_HOME,
	LE_EOF
}					t_termnum;

typedef	struct		s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

typedef	struct		s_le
{
	t_dlist			*history;
	char			*buff;
	char			*clipboard;
	char			tmp[LE_TMP_BUFF_SIZE];
	char			*prompt;
	int				prompt_size;
	int				prompt_type;
	int				buffer_size;
	int				max_size;
	int				cursor_x;
	int				cursor_y;
	int				cursor_buff;
	int				nb_char;
	int				nb_empty_char;
	int				nb_line;
	int				w_line;
	int				w_col;
	int				last_line;
	int				term;
	int				history_activ;
	int				copy_on;
	int				copy_off;
}					t_le;

/*
**	main.c
*/

char				*line_edition(int prompt, char **env);
int					le_read_and_exec(struct s_le *le_struct, char **env);
char				*le_interactif_disabled(void);

/*
**	le_init.c
*/

int					le_init(struct s_le *le_struct, char **env);
int					le_init_struct(struct s_le *le_struct, char **env);
void				le_init_calcul(struct s_le *le_struct);
int					le_init_set_attribute(struct termios *backup);

/*
**	le_exit.c
*/

int					le_exit(struct s_le *le_struct);
void				le_free(struct s_le *le_struct);
int					le_free_return(char *s1, char *s2, char *s3, int status);

/*
**	le_window.c
*/

int					le_window_size(int *col, int *line);
int					le_window_check(struct s_le *le_struct);
int					le_window_clear(struct s_le *le_struct);
int					le_window_clear_restore(struct s_le *le_struct);
int					le_window_clear_all_restore(struct s_le *le_struct);

/*
** le_termcap.c
*/

int					le_termcap_check(struct s_le *le_struct);
void				le_termcap_type(struct s_le *le_struct);
int					le_termcap_exec(struct s_le *le_struct);
int					le_termcap_motion(struct s_le *le_struct);
int					le_termcap_delete(struct s_le *le_struct);

/*
**	le_termcap_tool.c
*/

int					le_termcap_print(char *str, int nb);
int					le_ansi_print(int nb, char *s);
int					le_termcap_init(void);
int					le_rputchar(int c);

/*
**	le_buffer_tool.c
*/

void				le_buff_print(struct s_le *le_struct, int pos);
void				le_buff_print_select(struct s_le *le_struct,\
					int pos, int on, int off);
void				le_buff_truncate(struct s_le *le_struct, int *len);

/*
**	le_buffer_history.c
*/

int					le_buff_history(struct s_le *le_struct);
int					le_buff_history_forward(struct s_le *le_struct);
int					le_buff_history_backward(struct s_le *le_struct);
int					le_buff_history_clear(struct s_le *le_struct);

/*
**	le_buffer_operation.c
*/

int					le_buff_remove(struct s_le *le_struct, int i);
int					le_buff_add(struct s_le *le_struct, int i, char c);
int					le_buff_append(struct s_le *le_struct, char c);
int					le_buff_check_space(struct s_le *le_struct, int len);
int					le_buff_realloc(struct s_le *le_struct, int size);

/*
**	le_cursor_motion.c
*/

int					le_cursor_motion(struct s_le *le_struct, int motion);
int					le_cursor_right(struct s_le *le_struct);
int					le_cursor_left(struct s_le *le_struct);
int					le_cursor_up(struct s_le *le_struct);
int					le_cursor_down(struct s_le *le_struct);

/*
**	le_cursor_tool.c
*/

int					le_cursor_goto(int expected, int current,\
					struct s_le *le_struct);
int					le_cursor_restore(struct s_le *le_struct);
int					le_cursor_beggin(struct s_le *le_struct, int current);

/*
**	le_cursor.c
*/

int					le_cursor_word_forward(struct s_le *le_struct);
int					le_cursor_word_backward(struct s_le *le_struct);
int					le_cursor_home_end(struct s_le *le_struct, int direction);

/*
**	le_clipboard.c
*/

int					le_clipboard(struct s_le *le_struct);
int					le_clipboard_exec_cut(struct s_le *le_struct);
int					le_clipboard_copy(struct s_le *le_struct);
int					le_clipboard_paste(struct s_le *le_struct);
int					le_clipboard_cut(struct s_le *le_struct);

/*
**	le_prompt.c
*/

int					le_prompt_init(struct s_le *le_struct, char **env);
int					le_prompt_pwd(struct s_le *le_struct, char **env);
int					le_prompt_home(struct s_le *le_struct,\
					char **env, char *pwd);
int					le_prompt_quote(struct s_le *le_struct);
void				le_prompt_print(struct s_le *le_struct);

#endif
