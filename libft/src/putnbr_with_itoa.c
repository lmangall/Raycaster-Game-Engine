/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_with_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:38:20 by lmangall          #+#    #+#             */
/*   Updated: 2023/01/15 20:33:05 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	putnbr_with_itoa(int nbr)
{
	char	*str;
	int		count;

	str = ft_itoa(nbr);
	count = ft_putstr_fd(str, 1);
	free(str);
	return (count);
}
