/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:17 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 13:09:09 by lmangall         ###   ########.fr       */
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

mlx_texture_t	*return_missing_texture(void)
{
	uint32_t		red_pixel;
	unsigned int	i;

	mlx_texture_t *texture = malloc(sizeof(mlx_texture_t)); // Allocate memory
	if (texture)
	{
		texture->height = 64;
		texture->width = 64;
		texture->bytes_per_pixel = 4;
		texture->pixels = ft_calloc(texture->height * texture->width,
				sizeof(uint32_t));
		if (texture->pixels)
		{
			red_pixel = 0xFF000000; // Fully opaque red color
			red_pixel = reverse_bytes(red_pixel);
			i = 0;
			while (i < texture->height * texture->width)
			{
				texture->pixels[i] = red_pixel;
				i++;
			}
		}
		else
		{
			free(texture);
			return (NULL);
		}
	}
	else
	{
		return (NULL);
	}
	return (texture);
}

int	load_textures(t_data *data)
{
	t_textures	*textures;

	textures = ft_calloc(1, sizeof(t_textures));
	textures->north = mlx_load_png(data->map->textures_paths->north);
	if (textures->north == 0)
	{
		ft_printf("Error\nNorth texture not found\n");
		textures->north = return_missing_texture();
	}
	textures->south = mlx_load_png(data->map->textures_paths->south);
	if (textures->south == 0)
	{
		ft_printf("Error\nSouth texture not found\n");
		textures->south = return_missing_texture();
	}
	textures->west = mlx_load_png(data->map->textures_paths->west);
	if (textures->west == 0)
	{
		ft_printf("Error\nWest texture not found\n");
		textures->west = return_missing_texture();
	}
	textures->east = mlx_load_png(data->map->textures_paths->east);
	if (textures->east == 0)
	{
		ft_printf("Error\nEast texture not found\n");
		textures->east = return_missing_texture();
	}
	data->textures = textures;
	return (0);
}
