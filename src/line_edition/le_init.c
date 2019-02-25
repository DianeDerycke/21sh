/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:07:54 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/25 17:26:47 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_init(struct s_le *le_struct, char **env)
{
	if ((le_buff_check_space(le_struct, 1) == LE_REALLOC))
		if (le_buff_realloc(le_struct, 1))
			return (LE_FAILURE);
	if (le_struct->nb_char == LE_START)
	{
		if (le_prompt_init(le_struct, env))
			return (LE_FAILURE);
		le_struct->nb_char = 0;
		le_struct->cursor_x = le_struct->prompt_size;
	}
	else if (le_struct->tmp[0] == LE_EXIT || (le_struct->term == LE_EOF\
	&& !le_struct->nb_char))
	{
		ft_putchar(LE_ENDL);
		return (LE_EXIT);
	}
	else if (le_struct->tmp[0] == LE_ENDL)
	{
		le_cursor_goto(le_struct->nb_char, 1, le_struct);
		ft_putchar(LE_ENDL);
		le_struct->buff[le_struct->nb_char] = '\0';
		return (LE_ENDL);
	}
	le_init_calcul(le_struct);
	return (LE_SUCCESS);
}

/*
**	If the buffer is bigger than LE_BUFF_SIZE, it's reallocated
**	Initialise the prompt
**	Initialise nb_char and the cursor position
**	Check if the last char is interruption (end of text) or new line
**	If it's end, go at the end of the command line and print a new line
*/

int		le_init_struct(struct s_le *le_struct)
{
	if (!(le_struct->buff = (char *)malloc(sizeof(char *) * LE_BUFF_SIZE)))
		return (LE_FAILURE);
	ft_bzero(le_struct->buff, LE_BUFF_SIZE);
	if (le_window_size(&le_struct->w_col, &le_struct->w_line))
		return (LE_FAILURE);
	le_struct->nb_char = LE_START;
	le_struct->prompt_size = 0;
	le_struct->cursor_x = le_struct->prompt_size;
	le_struct->buffer_size = LE_BUFF_SIZE;
	le_struct->history_activ = 0;
	ft_bzero(le_struct->tmp, LE_TMP_BUFF_SIZE);
	if (hy_history_fill_list(le_struct) || !le_struct->history)
		le_struct->history_activ = -1;
	le_struct->clipboard = NULL;
	le_struct->copy_on = LE_START;
	le_struct->copy_off = LE_START;
	return (LE_SUCCESS);
}

/*
**	Initialise the line edition structure
**	Allocated the buffer at the BUFF_SIZE
**	w_col and w_line are the shells window size
**	nb_char is the number of char on the command line
**	cursor_x is the position of the cursor, initialise at the prompt size
**	buffer_size is the size of the buffer, when the buffer is realllocated,
**	the buffer_size = the buffer_size mulitplicated by himself
**	history_activ is for the management of the historic, when the user push
**	the up or down arrow, this value are set to 1, for know if the user want
**	to use historical command
**	history_fill_list, open (or create) and read the .21sh_history file,
**	and fill the list with the oldest commands
*/

void	le_init_calcul(struct s_le *le_struct)
{
	ft_strclr(le_struct->tmp);
	le_struct->term = 0;
	le_struct->cursor_buff = le_struct->cursor_x - le_struct->prompt_size;
	le_struct->cursor_y = ((le_struct->cursor_x - 1) / le_struct->w_col) + 1;
	le_struct->nb_line = ((le_struct->nb_char + le_struct->prompt_size)\
	/ le_struct->w_col) + 1;
	le_struct->last_line = le_struct->w_col - (le_struct->nb_line *\
		le_struct->w_col - (le_struct->nb_char + le_struct->prompt_size));
	le_struct->max_size = le_struct->w_col * le_struct->w_line\
		- le_struct->prompt_size;
}

/*
**	Initialise cursor_buff, real position on shell, with the prompt
**	Initialise cursor_y, line postion of the cursor, for avoid a division by 0
**	the number of line must be start at 1
**	Calculate nb_line, number of line on the command line
**	Initialise last_line, number of char on the last line
**	Calculate max_size, the maximum chars printable on the shell
*/

int		le_init_set_attribute(struct termios *backup)
{
	struct termios	s_set;

	if (tcgetattr(STDIN_FILENO, &s_set))
		return (LE_FAILURE);
	*backup = s_set;
	s_set.c_lflag &= ~(ICANON | ECHO | ISIG);
	if (tcsetattr(STDIN_FILENO, 0, &s_set))
		return (LE_FAILURE);
	return (LE_SUCCESS);
}

/*
**	Unset some attributes for the shell
**	~ICANON : No Cannonical mode
**	~ECHO : Don't echo the keyboard fraps
**	~ISIG : No sig nals
**	backup struct for save the last configuration of the shell
*/
