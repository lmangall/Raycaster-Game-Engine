/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:00:19 by lmangall          #+#    #+#             */
/*   Updated: 2023/06/11 10:42:53 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}

/*
int    main(void)
   {
       char s[] = "XmeBaby";
       int c = 'X';
       size_t n = 6;
       ft_memset(s, c, n);
       write (1, &s, 8);
       return (0);
   }
*/