/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:24:22 by lmangall          #+#    #+#             */
/*   Updated: 2023/05/10 13:33:46 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int arg)
{
	if (arg >= 'a' && arg <= 'z')
		arg = arg - 32;
	return (arg);
}
/*
int main(void)
{
    int c = 104;
    c = ft_toupper(c);
    write (1, &c, 1);
    write (1, "\n", 1);
}
*/