/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:02:18 by lmangall          #+#    #+#             */
/*   Updated: 2023/06/13 10:37:51 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = ft_calloc(1, 1);
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1) + 1;
	j = i + ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (j));
	if (!joined)
	{
		free((char *)s1);
		return (NULL);
	}
	ft_strlcpy(joined, s1, i);
	free((char *)s1);
	ft_strlcat(joined, s2, j);
	return (joined);
}

/*
int main (void)
{
    char const		s1[] = "Give me my s2 =>";
	char const		s2[] = "<= here I am, my dear s1";

    printf("%s\n", ft_strjoin(s1, s2));
	return (0);
}
*/