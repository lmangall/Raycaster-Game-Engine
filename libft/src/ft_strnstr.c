/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:29:59 by lmangall          #+#    #+#             */
/*   Updated: 2023/05/09 13:17:30 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	hlen;
	size_t	nlen;

	hlen = 0;
	if (*needle == '\0' || needle == NULL)
		return ((char *) haystack);
	while (haystack[hlen] != '\0' && hlen < len)
	{
		nlen = 0;
		while (needle[nlen] == haystack[hlen + nlen] && hlen + nlen < len)
		{
			if (needle[nlen + 1] == '\0')
			{
				return ((char *) haystack + hlen);
			}
			nlen++;
		}
		hlen++;
	}
	return (NULL);
}

/*
int main()
{

    char    *s1 = "haystackhaystackneedlehaystack";
    char    *s2 = "needle";
    size_t  len = strlen(s1);

    char    *i1 = strnstr(s1, s2, len);
    char    *i2 = ft_strnstr(s1, s2, len);


    printf("strnstr: %s\nft_strnstr: %s\n", i1,i2);
    return 0;
}
*/