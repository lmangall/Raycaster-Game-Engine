/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:34:17 by slombard          #+#    #+#             */
/*   Updated: 2023/02/12 20:53:15 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, int *count)
{
	if (n < 0)
	{
		ft_putchar('-', count);
		n = n * -1;
	}
	if (n >= 10)
		ft_putnbr(n / 10, count);
	ft_putchar((n % 10) + '0', count);
}
