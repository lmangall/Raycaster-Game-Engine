/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:11:38 by lmangall          #+#    #+#             */
/*   Updated: 2023/06/13 10:32:30 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	count;

	i = 0;
	if (!s)
		return (0);
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		count += ft_putchar_fd(s[i], fd);
		i++;
	}
	return (count);
}
