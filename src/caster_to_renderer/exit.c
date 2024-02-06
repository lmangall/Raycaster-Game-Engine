/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:15:52 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 22:06:31 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	my_mlx_delete_texture(mlx_texture_t *texture)
{
	if (texture != NULL)
	{
		if (texture->pixels != NULL)
			free(texture->pixels);
		free(texture);
	}
}

static void	free_textures(t_textures *textures)
{
	if (textures != NULL)
	{
		my_mlx_delete_texture(textures->north);
		my_mlx_delete_texture(textures->south);
		my_mlx_delete_texture(textures->west);
		my_mlx_delete_texture(textures->east);
		free(textures);
	}
}

static void	free_data(t_data *data)
{
	int	i;

	if (data->map != NULL)
	{
		if (data->map->grid != NULL)
		{
			i = 0;
			while (data->map->grid[i])
				free(data->map->grid[i++]);
			free(data->map->grid);
		}
		if (data->map->textures_paths != NULL)
			free(data->map->textures_paths);
		free(data->map);
	}
	if (data->player != NULL)
		free(data->player);
	if (data->ray != NULL)
		free(data->ray);
}

void	free_exit(t_data *data)
{
	int	i;

	i = 0;
	mlx_delete_image(data->mlx, data->img);
	mlx_close_window(data->mlx);
	free_textures(data->textures);
	free(data->textures);
	free_data(data);
	mlx_terminate(data->mlx);
	ft_putstr_fd("\nTschuess\n", 1);
	exit(0);
}
