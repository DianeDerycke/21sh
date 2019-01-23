/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 17:19:32 by mrandou           #+#    #+#             */
/*   Updated: 2019/01/14 17:35:41 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/lineedition.h"

/*					/!\ DELETE THIS FILE AT THE END /!\						  */
/*					/!\   DEBUG FUNCTIONS FOR TEST  /!\						  */


void	le_debug_fct(struct s_le *le_struct)
{
	int	fd;

	if ((fd = open("test.txt", O_WRONLY | O_CREAT | S_IRWXU)) == -1)
		return ;
	if ((write(fd, "\033[94mLINE EDITION TEST\n\n", ft_strlen("\033[94mLINE EDITION TEST\n\n"))) == -1)
		return ;
	if ((write(fd, "\033[32mPostion && Infos\n", ft_strlen("\033[32mPostion && Infos\n"))) == -1)
		return ;
	if ((write(fd, "\nCursor_x: ", ft_strlen("\nCursor_x: "))) == -1)
		return ;
	if ((write(fd, ft_itoa(le_struct->cursor_x), ft_nblen(le_struct->cursor_x))) == -1)
		return ;
	if ((write(fd, "\nCursor_y: ", ft_strlen("\nCursor_y: "))) == -1)
		return ;
	if ((write(fd, ft_itoa(le_struct->cursor_y), ft_nblen(le_struct->cursor_y))) == -1)
		return ;
	if ((write(fd, "\nCursor_real: ", ft_strlen("\nCursor_real: "))) == -1)
		return ;
	if ((write(fd, ft_itoa(le_struct->cursor_real), ft_nblen(le_struct->cursor_real))) == -1)
		return ;
	if ((write(fd, "\nPrompt_size: ", ft_strlen("\nPrompt_size: "))) == -1)
		return ;
	if ((write(fd, ft_itoa(le_struct->prompt_size), ft_nblen(le_struct->prompt_size))) == -1)
		return ;
	if ((write(fd, "\nnb_char: ", ft_strlen("\nnb_char: "))) == -1)
		return ;
	if ((write(fd, ft_itoa(le_struct->nb_char), ft_nblen(le_struct->nb_char))) == -1)
		return ;
	if ((write(fd, "\nnb_line: ", ft_strlen("\nnb_line: "))) == -1)
		return ;
	if ((write(fd, ft_itoa(le_struct->nb_line), ft_nblen(le_struct->nb_line))) == -1)
		return ;
	if ((write(fd, "\nlast_line: ", ft_strlen("\nlast_line: "))) == -1)
		return ;
	if ((write(fd, ft_itoa(le_struct->last_line), ft_nblen(le_struct->last_line))) == -1)
		return ;
	if ((write(fd, "\n\n\033[31mWindow Size\n", ft_strlen("\n\n\033[31mWindow Size\n"))) == -1)
		return ;
	if ((write(fd, "\nCol: ", ft_strlen("\nCol: "))) == -1)
		return ;
	if ((write(fd, ft_itoa(le_struct->w_col), ft_nblen(le_struct->w_col))) == -1)
		return ;
	if ((write(fd, "\nLine: ", ft_strlen("\nLine: "))) == -1)
		return ;
	if ((write(fd, ft_itoa(le_struct->w_line), ft_nblen(le_struct->w_line))) == -1)
		return ;
	motion_calcul(le_struct->cursor_real, le_struct->nb_char, le_struct->w_col, fd);
	if ((write(fd, "\n\n\n\033[0m", ft_strlen("\n\n\n\033[0m"))) == -1)
		return ;
	close(fd);
}

void    motion_calcul(int expected, int current, int col, int fd)
{
        int     diff;

        diff = current - expected;
        expected = (expected - 1) / col;
        current = (current - 1) / col;
        expected = expected - current;
        if ((write(fd,"\n\nEnd to cursor : ", ft_strlen("\n\nEnd to cursor : "))) == -1)
			return;
        if (expected > 0)
        {
            if ((write(fd, ft_itoa(expected), ft_nblen(expected))) == -1)
			return ;
			 if ((write(fd, " DOWN ", ft_strlen(" DOWN "))) == -1)
			return ;
        }
        else if (expected < 0)
        {
                expected *= -1;
			if ((write(fd, ft_itoa(expected), ft_nblen(expected))) == -1)
				return ;
			if ((write(fd, " UP ", ft_strlen(" UP "))) == -1)
				return ;
        }
        if (diff < 0)
                diff = -diff - (col * expected);
        else if (diff > 0)
                diff = (col * expected) - diff;
        if (diff > 0)
        {
			if ((write(fd, ft_itoa(diff), ft_nblen(diff))) == -1)
				return ;
			if ((write(fd, " RIGHT ", ft_strlen(" RIGHT "))) == -1)
				return ;
        }
        if (diff < 0)
        {
                diff *= -1;
				if ((write(fd, ft_itoa(diff), ft_nblen(diff))) == -1)
				return ;
			if ((write(fd, " LEFT ", ft_strlen(" LEFT "))) == -1)
				return ;
        }
}
