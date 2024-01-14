/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:39:19 by lmangall          #+#    #+#             */
/*   Updated: 2023/05/21 14:50:54 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (!ft_isascii(c))
		return ((char *) &str[i]);
	while (str[i])
	{
		if (str[i] == c)
			return ((char *) &str[i]);
		i++;
	}
	if (c == '\0')
		return ((char *) &str[i]);
	return (NULL);
}

/*
int    main (void)
{
		const char s[] = "trouve moi ca";
		char c = 'm';
		char *ret;
		ret = ft_strchr(s, c);

       printf("string after '%c' is: '%s'\n", c, ret);
}
*/