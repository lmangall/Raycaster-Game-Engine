/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:15:52 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/07 12:25:12 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void	free_textures(t_textures *textures)
{
	if (textures != NULL)
	{
		if (textures->north != NULL)
		{
			mlx_delete_texture(textures->north);
			textures->north = NULL;
		}
		if (textures->south != NULL)
		{
			mlx_delete_texture(textures->south);
			textures->south = NULL;
		}
		if (textures->west != NULL)
		{
			mlx_delete_texture(textures->west);
			textures->west = NULL;
		}
		if (textures->east != NULL)
		{
			mlx_delete_texture(textures->east);
			textures->east = NULL;
		}
		free(textures);
		textures = NULL;
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
			{
				free(data->map->grid[i]);
				data->map->grid[i] = NULL;
				i++;
			}
			free(data->map->grid);
			data->map->grid = NULL;
		}
		if (data->map->textures_paths != NULL)
		{
			free(data->map->textures_paths);
			data->map->textures_paths = NULL;
		}
		if (data->map->lines_arr != NULL)
		{
			free_str_arr(data->map->lines_arr);
			data->map->lines_arr = NULL;
		}
		free(data->map);
		data->map = NULL;
	}
	if (data->player != NULL)
	{
		free(data->player);
		data->player = NULL;
	}
	if (data->ray != NULL)
	{
		free(data->ray);
		data->ray = NULL;
	}
}

void	free_exit(t_data *data)
{
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	if (data->textures)
		free_textures(data->textures);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	if (data->mlx)
		free(data->mlx);
	free_data(data);
	ft_putstr_fd("\nTschuess\n", 1);
	exit(0);
}
