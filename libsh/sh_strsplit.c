/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:59:03 by dideryck          #+#    #+#             */
/*   Updated: 2018/10/16 16:40:48 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"
static int		ft_count_words(char const *s, int(*ft)(char))
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	if (s && s[0] == '\0')
		return (1);
	while (s[i])
	{
		while (ft(s[i]) && s[i])
			i++;
		if (!s[i])
			return (0);
		while (ft(s[i]) && s[i])
			i++;
		words++;
		while (ft(s[i]) && s[i])
			i++;
	}
	return (words + 1);
}

static int		ft_size_word(char const *s, int index, int(*ft)(char))
{
	int		size;

	size = 0;
	while (ft(s[index]) && s[index])
	{
		index++;
		size++;
	}
	return (size);
}

static char		**ft_fill_table(char **tab, char const *s, int(*ft)(char), int i)
{
	int		n;

	n = 0;
	while (s[i] && ft(s[i]))
		i++;
	if (!s[i])
		return (NULL);
	while (s[i] && n < ft_count_words(s, ft))
	{
		tab[n] = ft_strsub(s, i, ft_size_word(s, i, ft));
		if (!(tab[n]))
		{
			ft_free_array(tab);
			return (NULL);
		}
		while (ft(s[i]) && s[i])
			i++;
		n++;
		while (ft(s[i]) && s[i])
			i++;
	}
	tab[n] = NULL;
	return (tab);
}

char    **sh_strsplit(const char *s, int(*ft)(char))
{
	int		i;
	char	**tab;

	tab = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	if ((i = ft_count_words(s, ft)) == 0)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*) * i)))
		return (NULL);
	i = 0;
	return (ft_fill_table(tab, s, ft, i));
}