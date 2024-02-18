/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_elements_rgb_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:52:11 by slombard          #+#    #+#             */
/*   Updated: 2024/02/18 18:05:40 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

int	char_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (SUCCESS);
	else
		return (FAILURE);
}

int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (char_isdigit(str[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
