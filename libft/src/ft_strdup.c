/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:59:03 by lmangall          #+#    #+#             */
/*   Updated: 2023/06/13 13:06:29 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	length;
	char	*result;

	length = ft_strlen(src) + 1;
	result = (char *)malloc(length);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, src, length);
	return (result);
}
