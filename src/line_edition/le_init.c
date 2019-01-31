/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:07:54 by mrandou           #+#    #+#             */
/*   Updated: 2019/01/31 19:17:08 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_init(struct s_le *le_struct)
{
	if (le_struct->nb_char >= le_struct->buffer_size - 1)
		if (!(le_struct->buff = le_buff_realloc(le_struct, LE_BUFF_SIZE)) ||\
		 (le_struct->nb_char >= INT_MAX - 1))
			return (LE_FAILURE);
	if (le_struct->nb_char == LE_START)
	{
		le_init_prompt(le_struct);
		le_struct->nb_char = 0;
		le_struct->cursor_x = le_struct->prompt_size;
	}
	if (le_struct->tmp[0] == LE_ENDL)
	{
		le_cursor_goto(le_struct->nb_char, 1, le_struct);
		ft_putchar('\n');
		le_struct->buff[le_struct->nb_char] = '\0';
		return (LE_ENDL);
	}
	le_init_calcul(le_struct);
	return (LE_SUCCESS);
}	

/*
**	If the buffer is bigger than LE_BUFF_SIZE, it's reallocated
**	Print the prompt and initialise nb_char and the cursor posiotion
*/

void	le_init_prompt(struct s_le *le_struct)
{
	char *pwd;

	pwd = NULL;
	if (!le_struct->prompt_type)
	{
		// if (!(pwd = getenv("PWD")))
		// {
			ft_putstr(LE_PROMPT);
			le_struct->prompt_size = LE_PROMPT_SIZE + 1;
		// }
		// else
		// {
		// 	ft_putstr("\033[1m\033[32m");
		// 	ft_putstr(pwd);
		// 	ft_putstr(" > ");
		// 	ft_putstr("\033[0m");
		// 	le_struct->prompt_size = ft_strlen(pwd) + 3;
		// }
		
	}
	else
	{
		ft_putstr(LE_PROMPT_MIN);
		le_struct->prompt_size = 4;
	}
}

int		le_init_struct(struct s_le *le_struct)
{
	if (!(le_struct->buff = (char *)malloc(sizeof(char *) * LE_BUFF_SIZE)))
		return (LE_FAILURE);
	ft_bzero(le_struct->buff, LE_BUFF_SIZE);
	le_struct->nb_char = LE_START;
	le_struct->cursor_x = le_struct->prompt_size;
	le_struct->buffer_size = LE_BUFF_SIZE;
	le_struct->history_activ = 0;
	ft_bzero(le_struct->tmp, LE_TMP_BUFF_SIZE);
	if (hy_history_fill_list(le_struct) || !le_struct->history)
		le_struct->history_activ = -1;
	le_struct->clipboard = NULL;
	le_struct->copy_on = 0;
	le_struct->copy_off = 0;
	return (LE_SUCCESS);
}

/*
**	Allocated the buffer at the BUFF_SIZE
**	Initialise the line edition structure
**	nb_char is the number of char on the command line
**	cursor_x is the position of the cursor, initialise at the prompt size + 1
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
	le_cursor_calcul_empty_char(le_struct, le_struct->cursor_x);
	le_struct->cursor_buff = le_struct->cursor_x - le_struct->prompt_size;
	// le_struct->cursor_buff += le_struct->nb_empty_char;
	le_struct->cursor_y = ((le_struct->cursor_x - 1) / le_struct->w_col) + 1;
	if	(!le_struct->cursor_y)
		le_struct->cursor_y++;
	le_struct->nb_line = ((le_struct->nb_char + le_struct->prompt_size)\
	 / le_struct->w_col) + 1;
	le_struct->last_line = le_struct->w_col - (le_struct->nb_line *\
		le_struct->w_col - (le_struct->nb_char + le_struct->prompt_size));
}

/*
**	Initialise cursor_buff, real position on shell, with the prompt
**	Initialise cursor_y, line postion of the cursor, for avoid a division by 0
**	the number of line must be start at 1
**	Calculate nb_line, number of line on the command line
**	Initialise last_line, number of char on the last line
*/

int		le_set_attribute(struct termios *backup)
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

int		le_window_check(struct s_le *le_struct)
{
	int	col_new;
	int	line_new;

	if (!le_struct->w_col || !le_struct->w_line)
		return (LE_FAILURE);
	if (le_termcap_window_size(&col_new, &line_new))
		return (LE_FAILURE);
	if (le_struct->w_col != col_new || le_struct->w_line != line_new)
	{
		le_struct->w_col = col_new;
		le_struct->w_line = line_new;
		le_cursor_beggin(le_struct, le_struct->cursor_buff);
		le_termcap_print(TC_CLEAR_NEXT, 1);
		ft_putstr(LE_PROMPT);
		if (le_struct->nb_char)
			ft_putstr(le_struct->buff);
		if (le_cursor_goto(le_struct->cursor_x,\
		 (le_struct->nb_char + le_struct->prompt_size), le_struct))
		 	return (LE_FAILURE);
	}
	return (LE_SUCCESS);
}

/*
**	Check if the window was resize, if it's true, clear and print
**	Restore cursor position
*/

int		le_exit(struct s_le *le_struct, int ret)
{
	if (ret == LE_ENDL)
	{
		hy_dlst_free(le_struct->history);
		return (LE_EXIT);
	}
	if (ret == LE_FAILURE)
	{
		hy_dlst_free(le_struct->history);
		return (LE_FAILURE);
	}
	// if (*le_struct->buff == LE_EXIT)
	// {
	// 	tcsetattr(STDIN_FILENO, 0, backup);
	// 	ft_putendl("\n");
	// 	ft_putstr("\033[31mFINAL BUFFER ===> ");
	// 	ft_putendl(le_struct->buff);
	// 	ft_putstr("\033[0m");
	// 	return (LE_EXIT);
	// }
	return (LE_SUCCESS);
}

/*
**	Exit and set the old shell attribute
**	Just for the tests, I put the final buffer
*/

int		le_clear(struct s_le *le_struct)
{
	if (le_cursor_goto(le_struct->prompt_size, le_struct->cursor_x,\
	 le_struct))
		return (LE_FAILURE);
	if (le_termcap_print(TC_CLEAR_NEXT, 1))
		return (LE_FAILURE);
	ft_putstr(le_struct->buff);
	return (LE_SUCCESS);
}

int		le_clear_restore(struct s_le *le_struct)
{
	if (le_cursor_beggin(le_struct, le_struct->cursor_x - 1))
		return (LE_FAILURE);
	if (le_termcap_print(TC_CLEAR_NEXT, 1))
		return (LE_FAILURE);
	ft_putstr(LE_PROMPT);
	ft_putstr(le_struct->buff);
	if (le_cursor_beggin(le_struct, le_struct->nb_char \
	+ le_struct->prompt_size - 1))
		return (LE_FAILURE);
	if (le_cursor_restore(le_struct))
		return (LE_FAILURE);
	return (LE_SUCCESS);
}
