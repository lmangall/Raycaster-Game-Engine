/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:04:49 by lmangall          #+#    #+#             */
/*   Updated: 2023/05/09 13:39:34 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
/*
int main(void)
{
    char			src[] = "Pleaseletmebe";
    unsigned char	dest[] = "I will get you";
    size_t			n = 10;

	char	*s1 = memcpy(dest, src, n);
	char	*s2 = ft_memcpy(dest, src, n);
	printf ("memcpy: %s\nft_memcpy: %s\n", s1, s2);
}
*/