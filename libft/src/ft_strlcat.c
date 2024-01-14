/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:23:27 by lmangall          #+#    #+#             */
/*   Updated: 2023/05/09 13:17:22 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	t;

	dstlen = ft_strlen(dst);
	t = 0;
	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	while (src[t] != '\0' && dstlen + 1 < size)
	{
		dst[dstlen] = src[t];
		dstlen++;
		t++;
	}
	dst[dstlen] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[t]));
}

/*
while                as long as there is at least
                     one byte free in dst

    return (strlen(dst) + strlen(src));

     It will append at most size - strlen(dst) - 1 bytes, NUL-termi‐
     nating the result.

    return the initial length of dst plus the length of src
    */
/*
int main(void)
{
    const char src[] = "... my destination";
    char dst[] = "take me to ...";

    size_t size = 40;
     size_t r;

    r = ft_strlcat(dst, src, size);
     printf("%c\n", *dst);
     printf("%zu\n", r);
*/