/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:32:38 by lmangall          #+#    #+#             */
/*   Updated: 2023/05/09 13:29:42 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			len;
	unsigned char	*str;

	len = 0;
	str = (unsigned char *)s;
	while (++len <= n)
		if (*(str++) == (unsigned char)c)
			return ((void *)--str);
	return (0);
}
/*
int main (void)

{
const char s[] = "trouve moi ca";
char c = 'm';
char *ret;
size_t n = 12;

ret = ft_memchr(s, c, n);
printf("string after '%c' is: '%s'\n\n", c, ret);
ret = memchr(s, c, n);
printf("string after '%c' is: '%s'\n", c, ret);
}
*/
