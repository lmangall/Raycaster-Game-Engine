/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:55:40 by lmangall          #+#    #+#             */
/*   Updated: 2023/06/13 13:48:01 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (!str1 || !str2)
		return (1);
	while (str1[i] && str2[i] && (str1[i] == str2[i]) && (i < (n - 1)))
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
/*
int	main(void)
{
	char    s1[] = "aBcdefgh";
	char	s2[] = "abcdefgh";
	unsigned int	n;
    int ret;
	n = 5;
	ret = ft_strncmp(s1, s2, n);
	printf("%i\n", n);
    printf("%i\n", ret);
	printf("%d\n", strncmp(s1, s2, n));
    printf("%d\n", ft_strncmp(s1, s2, n));
	return (0);
}
*/