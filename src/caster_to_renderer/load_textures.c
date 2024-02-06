/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:17 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 22:37:26 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*remove_new_line_char_new(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\n')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	return (new_str);
}

int	load_textures(t_data *data)
{
	t_textures	*textures;

	ft_printf("\n\nLoading textures\n\n");
	textures = ft_calloc(1, sizeof(t_textures));
	textures->north = mlx_load_png(data->map->textures_paths->north);
	textures->south = mlx_load_png(data->map->textures_paths->south);
	textures->west = mlx_load_png(data->map->textures_paths->west);
	textures->east = mlx_load_png(data->map->textures_paths->east);
	data->textures = textures;
	return (0);
}
