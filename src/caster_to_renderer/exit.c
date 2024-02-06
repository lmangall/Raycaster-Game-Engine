/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:15:52 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 21:24:03 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_textures *textures)
{
	if (textures != NULL)
	{
		mlx_delete_texture(textures->north);
		mlx_delete_texture(textures->south);
		mlx_delete_texture(textures->west);
		mlx_delete_texture(textures->east);
		mlx_delete_texture(textures->floor);
		mlx_delete_texture(textures->ceiling);
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
		free(data->map);
	}
	if (data->player != NULL)
	{
		free(data->player);
	}
	if (data->ray != NULL)
	{
		free(data->ray);
	}
}

void	free_exit(t_data *data)
{
	int	i;

	i = 0;
	free_textures(data->textures);
	mlx_delete_image(data->mlx, data->img);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	free_data(data);
	ft_putstr_fd("Tschuess\n", 1);
	exit(0);
}
