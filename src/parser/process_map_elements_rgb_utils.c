/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_elements_rgb_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:52:11 by slombard          #+#    #+#             */
/*   Updated: 2024/02/05 15:52:12 by slombard         ###   ########.fr       */
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

	ft_printf("str_isdigit\n");
	ft_printf("str: %s\n", str);

	i = 0;
	while (str[i] != '\0')
	{
		ft_printf("str[i]: %c\n", str[i]);
		if (char_isdigit(str[i]) == FAILURE)
		{
			ft_printf("str_isdigit: FAILURE\n");
			return (FAILURE);

		}
		i++;
	}
	ft_printf("str_isdigit: SUCCESS\n");
	return (SUCCESS);
}
