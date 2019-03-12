#ifndef LEXER_H
#define LEXER_H

// # include "../libsh/libsh.h"
#define SUCCESS 0
#define FAILURE 1
#define ERROR -1
#define LEX_DQUOTE '\"'
#define LEX_SQUOTE '\''
#define BACKSLASH '\\'
#define SIZE_CONDITION 2
#define BUILTIN_SIZE 6
#define ARRAY_SIZE 6
#define INPUT_END 1
#define OUTPUT_END 0
#define ERRLEX_SIZE 5  
#define PERM 0677

typedef struct      s_param {
    char            *input;
    int             index;
    int           	token;
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

typedef enum    e_lex 
{
    UNEXPTOKEN = 5,
	UNDEFVAR,
	CNOTFOUND,
	PERMDENIED,
	UNEXPEOF,
	NOFILEDIR,
}               t_lex;

//LEX_INIT
t_param    	*init_param(void);
void    	free_ast(t_ast **ast);
void    	free_lexer(t_ast **ast);
void    	free_param(t_param *param);
int         push_node(char *value, int token, t_ast **node, int io_number);
t_ast     	*create_elem(void);
void        display_list(t_ast *lst);
void        display_tree(t_ast *tree, int lvl, int position);

//LEX UTILS ==> def type char function
int         lex_is_special_char(int c);
int         ft_isallowedsymb(int c);
int         ft_is_operator(int c);
int         ft_isidentifier(int c);
int         ft_is_single_quote(int c);
int         ft_is_double_quote(int c);
int         get_ast_op(char *c, int length);
char        *copy_until_ft(char *s, int *start, int(*f)(int c));
char        *copy_until_array_ft(char *s, int *start, int(*array[2])(int));

//LEX_ACTION
int     	whitespace_action(t_param *param);
int     	single_quote_action(t_param *param);
int     	double_quote_action(t_param *param);
int     	is_io_number(t_param *param);
int     	digit_action(t_param *param);
int     	operator_action(t_param *param);
int     	identifier_action(t_param *param);

//LEX INPUT
int     	lex_input(t_param *param);
int			get_valid_input(t_param *param, char **env, int ret);
int		verify_lexer(t_ast *ast);

//LEX_ERROR
char 		*getter_error_var(char *str);
int         get_error(int error_nb, char *str);

//EXEC FUNCTION
int      	is_command(t_sh *shell);
int    		treat_command(t_sh *shell, t_ast *ast);
int     	exec_cmd(t_ast *ast, t_sh *shell);
int     	exec_pipe_cmd(t_sh *shell, t_ast *ast);

//EXPANSIONS
ssize_t		apply_expansions(t_sh *shell, t_ast *ast);

//PARSE EXECUTION
int    		parser_execution(t_ast *ast, t_sh *shell);

//PARSER
t_ast     *create_ast(t_ast *curr_node, t_ast *start, t_ast *end);

//PIPE
int 		do_pipe(t_sh *shell, t_ast *ast);

//PIPE_UTILS
t_pid 	    *get_pid_list(t_pid *new_list);
void		close_pipe(int *fd);
void		close_dup(int *fd, int std);

//QUOTES
int			handle_quotes(char **input);
int     	is_valid_quotes(char *str);

//REDIR_FUNCTIONS
int		redir_great(t_ast *redir, t_ast *ast);
int		redir_dgreat(t_ast *redir, t_ast *ast);
int     redir_less(t_ast *redir, t_ast *ast);
int     redir_dless(t_ast *redir, t_ast *ast);
int     redir_and(t_ast *redir, t_ast *ast);
int     redir_greatand(t_ast *redir, t_ast *ast);
int     redir_lessand(t_ast *redir, t_ast *ast);

//REDIR
int    *getter_std(int init);
void    reset_std(int *fd);
int     open_file(t_ope token, char *file);
int    exec_redirection(t_ast *ast, t_sh *shell);

//HEREDOC
int     handle_heredoc(char *file);
char    *prompt_heredoc(char *end_word);


//REDIR UTILS
t_ast  *find_next_redir(t_ast *ast);
t_ast    *add_argument_to_cmd(t_ast *ast);
int     get_str_redir(t_ope token);



//ERROR CASE
ssize_t     error_arg(void);
int     	error_execution(char *cmd_name);
void		error_option(char c);
ssize_t		too_many_args(char *cmd);
ssize_t		unvalid_setenv_cmd(void);
ssize_t		error_chdir(int error, char *path, char *cmd);
int			syntax_error(char *str);
int			ambiguous_redirect(char *arg);

//==========================================================//

//builtin
int			find_builtin(char *cmd);
int     	exec_builtin(t_sh *shell);

//builtin minishell part added
ssize_t		ms_echo(char **split_cmd, char ***ms_env, int ret);
ssize_t		ms_cd(char **split_cmd, char ***ms_env, int ret);
ssize_t		ms_setenv(char **split_cmd, char ***ms_env, int ret);
ssize_t		ms_unsetenv(char **split_cmd, char ***ms_env, int ret);
ssize_t		ms_env(char **split_cmd, char ***ms_env, int ret);
ssize_t     ms_exit(char **split_cmd, char ***ms_env, int ret);
//utils2.c
char		**find_first_bin(char **split_cmd, int c);
size_t		getnbr_args(char **split_cmd, int c);
void		copy_add_var_to_env(char ***env, char *name, char *value);
ssize_t		exec_simple_env(char **cmd, char **s_bin, char **env);
void	    init_opt_struct(t_opt *env_opt);
void		init_env_options(char **split_cmd, t_opt *env_opt);
void		valid_option(char c, t_opt *env_opt);
void		add_argument_to_env(char **split_cmd, char ***env);
char		**add_variable(char *v_name, char *v_value, char **ms_env);

#endif
