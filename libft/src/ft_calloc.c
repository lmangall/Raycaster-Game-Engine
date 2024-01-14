/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:56:45 by lmangall          #+#    #+#             */
/*   Updated: 2023/06/12 22:31:01 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb == 0 || size == 0)
		return (NULL);
	p = malloc(size * nmemb);
	if (!p)
		return (NULL);
	ft_bzero (p, size * nmemb);
	return (p);
}
/*
int main() 
{

    int* a = (int*) ft_calloc(5, sizeof(int));

    return 0;
}
*/
/*BETTER APPROACH ?  =>
void	*ft_calloc(size_t nitems, size_t len)
{
	void	*ptr;
	size_t	lentotal;

	if (nitems >= INT_MAX || len >= INT_MAX)
		return (NULL);
	lentotal = nitems * len;
	ptr = malloc(lentotal);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, lentotal);
	return (ptr);
}
*/