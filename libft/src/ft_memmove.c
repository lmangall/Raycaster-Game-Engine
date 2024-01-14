/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:08:27 by lmangall          #+#    #+#             */
/*   Updated: 2023/05/09 13:40:01 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t n)
{
	unsigned char		*tempdst;
	const unsigned char	*tempsrc;
	size_t				i;

	if (!dst || !src)
		return (0);
	tempdst = (unsigned char *)dst;
	tempsrc = (unsigned char *)src;
	i = 0;
	if (tempsrc < tempdst)
		while (++i <= n)
			tempdst[n - i] = tempsrc[n - i];
	else
		while (n-- > 0)
			*(tempdst++) = *(tempsrc++);
	return (dst);
}
/*
int main(void)
{
    char src[] = "Pleaseletmebe";
    unsigned char dest[] = "I will get you";
    size_t n = 10;
    ft_memmove(dest, src, n);
    write(1, &dest, 14);
}
*/
/*
IF src is before(czyli smaller than) dest (as pointer address)
 copz from src to dest starting by end

    unsigned char *temp;
    temp = dest;
    unsigned char *tempsrc;
    tempsrc = src;
    while (n != 0)
    {
        *temp = *tempsrc;
        n--;
        temp++;
        src++;
    }
    return (dest);

}

*/