/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:18:40 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 14:56:36 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/process_cmd.h"
#include "../../includes/error.h"

static void		join_tilde_expansion(char *home, char **arg)
{
	char 	*tmp;

	tmp = NULL;
	if (!(tmp = ft_strdup((*arg) + 1)))
		sh_malloc_error();
	ft_strdel(arg);
	if (!(*arg = ft_strjoin_free(home, tmp)))
		sh_malloc_error();
	ft_strdel(&tmp);
}

static ssize_t		tilde_expansion(char **arg, char **env)
{
	char	*home;
	size_t	pos;

	if ((!arg || !(*arg) || !env || sh_find_variable(HOME, env, &pos) == -1))
		return (FAILURE);
	if (!(home = sh_get_var_value(env[pos])))
		return (FAILURE);
	if ((*arg)[0] == C_TILDE)
	{
		if (ft_strlen(*arg) == 1)
		{
			ft_strdel(arg);
			*arg = home;
		}
		else if (ft_strlen(*arg) >= 1 && (*arg)[1] == C_SLASH)
			join_tilde_expansion(home, arg);
		else
			ft_strdel(arg);
	}
	return (SUCCESS);
}

static int			concat_d_expansion(char *ptr, char *arg, t_expansion *st,
					char **env)
{
	if (!(st->sub = (ptr != arg ? ft_strsub(arg, 0, (size_t)(ptr - arg)) :
	ft_strdup(""))))
		sh_malloc_error();
	if ((st->v_value = sh_get_var_path(ptr + 1, env, &st->index)) != NULL)
	{
		if (st->join && (st->join[0]))
		{
			ft_strdel(&st->sub);
			st->sub = ft_strndup(st->join, ft_strlen(st->join) - st->index - 1);
			ft_strdel(&st->join);
			st->join = NULL;
		}
		if (!(st->join = ft_strjoin_free(st->sub, st->v_value)) ||
		!(st->sub = ft_strsub(ptr + 1, st->index, ft_strlen(ptr + st->index)))
		|| !(st->join = ft_strjoin_free(st->join, st->sub)))
			sh_malloc_error();
		ft_strdel(&st->v_value);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

static int			dollar_expansion(char **cmdline, char **env, char *arg,
										char *ptr)
{
	t_expansion	st;

	st.index = 0;
	st.join = NULL;
	while (ptr)
	{
		if (concat_d_expansion(ptr, arg, &st, env) == FAILURE)
			return (FAILURE);
		ft_strdel(&st.sub);
		arg = ptr + st.index;
		ptr = ft_strchr(ptr + st.index + 1, VAL_DOLLAR);
	}
	ft_strdel(cmdline);
	*cmdline = st.join;
	return (SUCCESS);
}

ssize_t				apply_expansions(t_sh *shell, t_ast *ast)
{
	char		*ptr;
	int			ret;

	ret = 0;
	ptr = NULL;
	while (ast)
	{
		if (ast->token != SQUOTE)
		{
			if (ast->value && (ptr = ft_strchr(ast->value, VAL_DOLLAR))
			&& ft_strlen(ast->value) > 1)
				ret = dollar_expansion(&(ast->value), shell->env, ast->value, ptr);
			else if (ast->value && ((ft_strcmp(ast->value, "~") == SUCCESS)
			|| ft_strchr(ast->value, VAL_TILDE)))
				ret = tilde_expansion(&(ast->value), shell->env);
		}
		if (ret == FAILURE)
			return (get_error(UNDEFVAR, ast->value));
		ast = ast->left;
	}
	return (SUCCESS);
}