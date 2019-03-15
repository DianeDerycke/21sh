/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:38:44 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/15 14:39:28 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_remove_char(char *str, char c)
{
    int     i;

    i = 0;
    if (!str || !c)
        return (1);
    while (str[i])
    {
        while (str[i] && str[i] == c && str[i + 1])
            ft_memmove(&str[i], &str[i + 1], ft_strlen(str + i));
        if (str[i] == c && !str[i + 1])
            str[i] = '\0';
        i++;
    }
    return (0);
}