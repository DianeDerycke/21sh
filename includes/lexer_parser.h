/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:00:15 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/18 16:03:29 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

# include "../libsh/libsh.h"
# define BACKSLASH '\\'
# define SIZE_CONDITION 2
# define ARRAY_SIZE 6

typedef struct		s_param {
	char			*input;
	int				index;
	int				token;
	int				(*ft)(int);
	struct s_ast	*l_tokens;
}					t_param;

t_param				*init_param(void);
void				free_ast(t_ast **ast);
void				free_lexer(t_ast **ast);
void				free_param(t_param *param);
int					push_node(char *value, int token, t_ast **node,
							int io_number);
t_ast				*create_elem(void);
void				display_list(t_ast *lst);
void				display_tree(t_ast *tree, int lvl, int position);

char				*get_operator(int index);
int					get_ast_op(char *c, int length);
char				*copy_until_array_ft(char *s, int *start,
						int(*array[2])(int));
int					ft_isallowedsymb(int c);
int					ft_is_operator(int c);
int					ft_isidentifier(int c);
int					ft_is_single_quote(int c);
int					ft_is_double_quote(int c);

int					whitespace_action(t_param *param);
int					single_quote_action(t_param *param);
int					double_quote_action(t_param *param);
int					is_io_number(t_param *param);
int					digit_action(t_param *param);
int					operator_action(t_param *param);
int					identifier_action(t_param *param);

int					lex_input(t_param *param);
int					get_valid_input(t_param *param, char **env, int ret);
int					verify_lexer(t_ast *ast);

t_ast				*create_ast(t_ast *curr_node, t_ast *start, t_ast *end);

#endif
