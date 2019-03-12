/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:50:43 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/12 00:19:49 by DERYCKE          ###   ########.fr       */
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
# define IS_PIPE '|'
# define HEREDOC 42
# define BUFF_SIZE 4096
# define REDIR_SIZE 15
# define SUCCESS 0
# define FAILURE 1
# define ERROR -1
# define NOT_FOUND 0
# define ACCESS_D 1

typedef enum    e_ope {
    SEPARATOR, //   ;
    PIPE,      //   |
    WORD,      //   [aA-zZ.. 0..9]
    GREAT,     //   >
    DGREAT,    //   >>
    LESS,      //   <
    DLESS,     //   <<
    AND,       //   &
    LESSAND,   //   <&
    GREATAND,  //   >&
    DIGIT,      // [0..9]
    DQUOTE = '\"', 
    SQUOTE = '\'',
}               t_ope;

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct      s_pid
{
    int             proc;
    struct s_pid    *next;
}                   t_pid;

typedef struct      s_ast {
    char            *value;
    int             token;
    int             io_number;
    int             from;
    int             to;
    int             std;
    struct s_ast  *next;
    struct s_ast  *right;
    struct s_ast  *left;
}                   t_ast;

typedef struct      s_sh {
    char            **env;
    char            **cmd;
    char            *path;
    int             fork;
    int             exec;
    struct s_pid    *l_pid;
}                   t_sh;


/*
** list functions
*/

int         sh_exec_binary(t_sh *shell);
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
int			sh_get_size_rtree(t_ast *ast);
char		**sh_rtree_to_array(t_ast *ast);
t_sh 		*init_shell(void);
void		sh_free_shell(t_sh *shell);
char		*sh_strinsert(char *dst, char *src, int pos);

t_pid       *sh_pidnew(int pid);
int         sh_push_pidnew(int pid, t_pid **list);
void        sh_freepidlist(t_pid **list);

#endif
