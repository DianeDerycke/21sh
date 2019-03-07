/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:18:40 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/06 22:09:47 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static ssize_t		tilde_expansion(char **arg, char **env)
{
	char	*tmp;
	char	*home;
	size_t	pos;

	if ((!arg || !(*arg) || !env || ms_find_variable(HOME, env, &pos) == -1))
		return (FAILURE);
	if (!(home = ms_get_var_value(env[pos])))
		return (FAILURE);
	tmp = NULL;
	if ((*arg)[0] == C_TILDE)
	{
		if (ft_strlen(*arg) > 1 && (*arg)[1] == C_SLASH)
		{
			if (!(tmp = ft_strdup((*arg) + 1)))
				ms_malloc_error();
			ft_strdel(arg);
			if (!(*arg = ft_strjoin_free(home, tmp)))
				ms_malloc_error();
			ft_strdel(&tmp);
		}
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
		ms_malloc_error();
	if ((st->v_value = ms_get_var_path(ptr + 1, env, &st->index)) != NULL)
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
			ms_malloc_error();
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
		{
			getter_error_var(ast->value);
			return (FAILURE);
		}
		ast = ast->left;
	}
	return (SUCCESS);
}
