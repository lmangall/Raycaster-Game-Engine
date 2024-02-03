/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:33:42 by slombard          #+#    #+#             */
/*   Updated: 2023/02/12 20:43:01 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_hex(unsigned int hex, int *count, char c)
{
	if (c == 'x')
		ft_puthex(hex, count, c);
	if (c == 'X')
		ft_puthex(hex, count, c);
}
