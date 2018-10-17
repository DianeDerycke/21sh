/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:50:43 by dideryck          #+#    #+#             */
/*   Updated: 2018/10/17 16:18:17 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSH_H
# define LIBSH_H

#include "../libft/libft.h"

# ifndef PROMPT
#  define PROMPT "\033[1m\033[32m∴ ➢ \033[0m"
# endif

# define C_EQUAL '='
# define SH21 "21sh"
# define SUCCESS 0
# define ERROR 1
# define BUFF_SIZE 4096

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;


int		sh_strfpos(char *str, char oc);
char	**sh_strsplit(const char *s, int(*ft)(char));

/*
** list functions
*/
t_env		*sh_create_elem(void);
#endif
