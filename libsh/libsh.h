/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:50:43 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/16 14:00:45 by DERYCKE          ###   ########.fr       */
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
    int             std;
    char            *heredoc;
    struct s_ast  *next;
    struct s_ast  *right;
    struct s_ast  *left;
}                   t_ast;

typedef struct      s_sh {
    char            **env;
    char            **cmd;
    char            *path;
    int             fork;
    struct s_pid    *l_pid;
}                   t_sh;


/*
** list functions
*/

int         sh_exec_binary(t_sh *shell);
int			sh_get_size_rtree(t_ast *ast);
char		**sh_rtree_to_array(t_ast *ast);
t_sh 		*init_shell(void);
void		sh_free_shell(t_sh *shell);
char		*sh_strinsert(char *dst, char *src, int pos);
t_pid       *sh_pidnew(int pid);
int         sh_push_pidnew(int pid, t_pid **list);
void        sh_freepidlist(t_pid **list);

#endif
