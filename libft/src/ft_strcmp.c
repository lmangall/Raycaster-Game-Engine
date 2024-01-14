/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:53:22 by lmangall          #+#    #+#             */
/*   Updated: 2023/05/09 14:11:45 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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