/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:50:43 by dideryck          #+#    #+#             */
/*   Updated: 2019/01/23 17:18:01 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSH_H
# define LIBSH_H

#include "../libft/libft.h"

# ifndef PROMPT
#  define PROMPT "\033[1m\033[32m∴ ➢ \033[0m"
# endif

# define C_EQUAL '='
# define BUFF_SIZE 4096

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

/*
** list functions
*/

int			sh_strfpos(char *str, char oc);
char		**sh_strsplit(const char *s, int(*ft)(char));
char		*sh_getvalue(t_env *env, char *key);
char		*sh_get_env_value(char **env, char *key);
char		**sh_add_field_array(char **tab, char *newfield);
void		sh_remove_field_array(char **tab, int field);
int			sh_find_env_key(char **env, char *key);
void		sh_append_env_value(char **env, char *key, char *newvalue);
char		*sh_get_env_key(char **env, int field);
// void		sh_env_display(char **env);

#endif
