/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:20:43 by lmangall          #+#    #+#             */
/*   Updated: 2023/05/07 14:23:25 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *arg)
{
	size_t	i;

	i = 0;
	while (*arg != '\0')
	{
		arg++;
		i++;
	}
	return (i);
}
/*
int main(void)
{
    char str[] = "countme";
    size_t cnt = ft_strlen(str);
    cnt += '0';
    write (1, &cnt, 1);
    return (0);
}
*/