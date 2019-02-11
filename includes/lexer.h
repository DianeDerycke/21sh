#ifndef LEXER_H
#define LEXER_H

# include "../libsh/libsh.h"
#define SUCCESS 0
#define FAILURE 1
#define ERROR -1
#define LEX_DQUOTE '\"'
#define LEX_SQUOTE '\''
#define BACKSLASH '\\'
#define SIZE_CONDITION 2
#define BUILTIN_SIZE 6
#define ARRAY_SIZE 6
#define SH_STDIN 0
#define SH_STDOUT 1
#define SH_STDERR 2
#define INPUT_END 1
#define OUTPUT_END 0

typedef struct      s_param {
    char            *input;
    int             index;
    int           token;
    int(*ft)(int);
    struct s_ast  *l_tokens;
}                   t_param;

typedef struct      s_builtin
{
    char            name[20];
    ssize_t			(*function)(char **, char ***, int);
}                   t_builtin;


typedef struct		s_expansion
{
	char	*tmp;
	char	*sub;
	char	*join;
	char	*v_value;
	int		index;
}					t_expansion;

typedef struct		s_opt
{
	ssize_t			i;
	ssize_t			p;
	ssize_t			s;
	ssize_t			u;
	ssize_t			v;
}					t_opt;


//def type char function
int         ft_isallowedsymb(int c);
int         ft_is_operator(int c);
int         ft_is_single_quote(int c);
int         ft_is_double_quote(int c);
int         ft_isidentifier(int c);
int         lex_is_special_char(int c);


//token
int         get_ast_op(char *c, int length);


// list function
void        display_list(t_ast *lst);
int         push_node(char *value, int token, t_ast **node);
t_ast     *create_elem(void);

//utils
char        *copy_until_ft(char *s, int *start, int(*f)(int c));
char        *copy_until_array_ft(char *s, int *start, int(*array[2])(int));


//lex_action
int     whitespace_action(t_param *param);
int     single_quote_action(t_param *param);
int     double_quote_action(t_param *param);
int     io_number_action(t_param *param);
int     digit_action(t_param *param);
int     operator_action(t_param *param);
int     identifier_action(t_param *param);

//lex_init
void    init_param(t_param **param);

//Quotes
int     valid_quotes(char *str);

//ERROR CASE
ssize_t     error_arg(void);
int     error_execution(char *cmd_name);


//parser
t_ast     *parser_input(t_ast *curr_node, t_ast *start, t_ast *end);

//parser_utils
void        display_tree(t_ast *tree, int lvl, int position);

//parser_exec
int    parser_execution(t_ast *ast);
int     exec_cmd(t_ast *ast);
ssize_t		apply_expansions(t_sh *shell);

//exec.c
void     do_pipe(t_ast *ast);
// void	do_pipe(t_ast *ast);
t_ast  *find_next_redir(t_ast *ast);
int    exec_redirection(t_ast *ast);


//builtin
ssize_t		ms_echo(char **split_cmd, char ***ms_env, int ret);
ssize_t		ms_cd(char **split_cmd, char ***ms_env, int ret);
ssize_t		ms_setenv(char **split_cmd, char ***ms_env, int ret);
ssize_t		ms_unsetenv(char **split_cmd, char ***ms_env, int ret);
ssize_t		ms_env(char **split_cmd, char ***ms_env, int ret);
ssize_t     ms_exit(char **split_cmd, char ***ms_env, int ret);
int			find_builtin(char *cmd);

//error
void		error_option(char c);
ssize_t		too_many_args(char *cmd);
ssize_t		unvalid_setenv_cmd(void);
ssize_t		error_chdir(int error, char *path, char *cmd);

//utils2.c
char		**find_first_bin(char **split_cmd, int c);
size_t		getnbr_args(char **split_cmd, int c);
void		copy_add_var_to_env(char ***env, char *name, char *value);

//init.c
ssize_t		exec_simple_env(char **cmd, char **s_bin, char **env);
void	    init_opt_struct(t_opt *env_opt);
void		init_env_options(char **split_cmd, t_opt *env_opt);
void		valid_option(char c, t_opt *env_opt);
//env.c
void		add_argument_to_env(char **split_cmd, char ***env);

// setenv.c
char		**add_variable(char *v_name, char *v_value, char **ms_env);

// redir
int		redir_great(t_ast *ast);




#endif