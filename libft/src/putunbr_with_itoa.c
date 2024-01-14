/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putunbr_with_itoa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:38:20 by lmangall          #+#    #+#             */
/*   Updated: 2023/01/15 20:47:21 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = get_len(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (0);
	num[len] = '\0';
	while (n != 0)
	{
		num[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (num);
}

int	putunbr_with_itoa(unsigned int nbr)
{
	char	*str;
	int		count;

	count = 0;
	if (nbr == 0)
		count += write(1, "0", 1);
	else
	{
		str = ft_uitoa(nbr);
		count = ft_putstr_fd(str, 1);
		free(str);
	}
	return (count);
}
