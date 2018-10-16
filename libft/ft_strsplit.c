/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 18:02:44 by dideryck          #+#    #+#             */
/*   Updated: 2018/09/20 14:57:36 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_words(char const *s, char c)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	if (*s == '\0')
		return (1);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			return (0);
		while (s[i] != c && s[i])
			i++;
		words++;
		while (s[i] == c && s[i])
			i++;
	}
	return (words + 1);
}

static int		ft_size_word(char const *s, int index, char c)
{
	int		size;

	size = 0;
	while (s[index] != c && s[index])
	{
		index++;
		size++;
	}
	return (size);
}

static char		**ft_fill_table(char **tab, char const *s, char c, int i)
{
	int		n;

	n = 0;
	while (s[i] == c && s[i])
		i++;
	if (!s[i])
		return (NULL);
	while (s[i] && n < ft_count_words(s, c))
	{
		tab[n] = ft_strsub(s, i, ft_size_word(s, i, c));
		if (!(tab[n]))
		{
			ft_free_array(tab);
			return (NULL);
		}
		while (s[i] != c && s[i])
			i++;
		n++;
		while (s[i] == c && s[i])
			i++;
	}
	tab[n] = NULL;
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	char	**tab;

	tab = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	if ((i = ft_count_words(s, c)) == 0)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*) * i)))
		return (NULL);
	i = 0;
	return (ft_fill_table(tab, s, c, i));
}
