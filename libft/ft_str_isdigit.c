/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:14:09 by dideryck          #+#    #+#             */
/*   Updated: 2019/02/21 15:15:13 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

int     ft_str_isdigit(char *str)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]))
            i++;
        else
            return (0);
    }
    return (1);
}