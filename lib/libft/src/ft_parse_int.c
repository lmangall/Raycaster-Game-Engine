/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:39:36 by slombard          #+#    #+#             */
/*   Updated: 2023/02/12 20:56:06 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_int(int nbr, int *count)
{
	if (nbr == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}	
	ft_putnbr(nbr, count);
}
