/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:04:49 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/02 02:02:59 by slombard         ###   ########.fr       */
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
int	main(void)
{
	char			src[] = "Pleaseletmebe";
	unsigned char	dest[] = "I will get you";
	size_t			n;
	char			*s1;
	char			*s2;

	n = 10;
	s1 = memcpy(dest, src, n);
	s2 = ft_memcpy(dest, src, n);
	printf ("memcpy: %s\nft_memcpy: %s\n", s1, s2);
}
*/