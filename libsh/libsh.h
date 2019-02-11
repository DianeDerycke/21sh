/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:50:43 by dideryck          #+#    #+#             */
/*   Updated: 2019/02/11 15:25:27 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSH_H
# define LIBSH_H

#include "../libft/libft.h"
#include "../libms/libms.h"
# ifndef PROMPT
#  define PROMPT "\033[1m\033[32m∴ ➢ \033[0m"
# endif

# define C_EQUAL '='
# define BUFF_SIZE 4096
# define REDIR_SIZE 1
# define SUCCESS 0
# define FAILURE 1
# define ERROR -1

static char     operators[20][20] = {
    {";"},
    {"|"},
    ("\n"),
    {"\n"},
    {"\n"},
    {">"},
    {">>"},
    {"<"},
    {"<<"},
    {"&"},
    {"<&"},
    {">&"},
    {"\0"},
};

typedef enum    e_ope{
    SEPARATOR, //   ;
    PIPE,      //   |
    NEWLINE,   //   \n
    WORD,      //   [aA-zZ.. 0..9]
    GREAT,     //   >
    DGREAT,    //   >>
    LESS,      //   <
    DLESS,     //   <<
    AND,       //   &
    LESSAND,   //   <&
    GREATAND,  //   >&
    IO_NUMBER,  //   [0,1,2...] Digit with '<' or '>' as delimiter
    DIGIT,      // [0..9]
    DQUOTE = '\"', 
    SQUOTE = '\'',
    C_DOLLAR = '$',
}               t_ope;

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;


typedef struct      s_sh {
    char            **env;
    char            **cmd;
}                   t_sh;

typedef struct      s_ast {
    char            *value;
    int             token;
    int             pipecall;
    int             fd1;
    int             fd0;
    struct s_ast  *next;
    struct s_ast  *right;
    struct s_ast  *left;
}                   t_ast;

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
int         sh_get_size_rtree(t_ast *start, t_ast *end);
char        **sh_rtree_to_array(t_ast *start, t_ast *end);
t_sh 		*sh_get_shell(t_ast *start, t_ast *end);
void		sh_free_shell(t_sh *shell);

#endif
