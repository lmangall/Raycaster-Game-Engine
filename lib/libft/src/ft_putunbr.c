/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:39:19 by slombard          #+#    #+#             */
/*   Updated: 2023/02/12 20:53:41 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putunbr(unsigned int n, int *count)
{
	if (n >= 10)
	{
		ft_putunbr((n / 10), count);
		ft_putunbr((n % 10), count);
	}
	else
		ft_putchar((n + 48), count);
}
