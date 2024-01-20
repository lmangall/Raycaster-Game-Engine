/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:23:15 by lmangall          #+#    #+#             */
/*   Updated: 2023/06/13 10:41:07 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*stored_s_to_str(char *stored_s)
{
	int		i;
	char	*str;

	i = 0;
	if (!stored_s[i])
		return (NULL);
	while (stored_s[i] && stored_s[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (stored_s[i] && stored_s[i] != '\n')
	{
		str[i] = stored_s[i];
		i++;
	}
	if (stored_s[i] == '\n')
	{
		str[i] = stored_s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*new_stored_s(char *stored_s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (stored_s[i] && stored_s[i] != '\n')
		i++;
	if (!stored_s[i])
	{
		free(stored_s);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(stored_s) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (stored_s[i])
		str[j++] = stored_s[i++];
	str[j] = '\0';
	free(stored_s);
	return (str);
}
