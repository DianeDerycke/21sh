/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 17:10:18 by mrandou           #+#    #+#             */
/*   Updated: 2019/01/27 17:10:19 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE 1
#define ERROR -1
#define DOLLAR '$'
#define LEX_DQUOTE '\"'
#define LEX_SQUOTE '\''
#define BACKSLASH '\\'
#define SIZE_CONDITION 2
#define ARRAY_SIZE 6

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
	{"\0"}
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
	C_DOLLAR = '$'
}               t_ope;

typedef struct      s_param {
	char            *input;
	int             index;
	int           token;
	int(*ft)(int);
	struct s_token  *l_tokens;
}                   t_param;

typedef struct      s_token {
	char            *value;
	t_ope            token;
	struct s_token  *next;
	struct s_token  *right;
	struct s_token  *left;
}                   t_token;

//def type char function
int         ft_isallowedsymb(int c);
int         ft_is_operator(int c);
int         ft_is_single_quote(int c);
int         ft_is_double_quote(int c);
int         ft_isidentifier(int c);
int         lex_is_special_char(int c);


//token
int         get_token_op(char *c, int length);


// list function
void        display_list(t_token *lst);
int         push_node(char *value, int token, t_token **current_node);
t_token     *create_elem(void);

//utils
char        *copy_until_ft(char *s, int *start, int(*f)(int c));
char        *copy_until_array_ft(char *s, int *start, int(*tab[2])(int));


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

//parser
t_token     *parser_input(t_token *start, t_token *end);
void        display_tree(t_token *tree, int lvl, int position);


#endif
