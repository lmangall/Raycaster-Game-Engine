/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:15:52 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/07 12:11:05 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

// static void free_textures(t_textures *textures)
// {
//     if (textures != NULL)
//     {
//         // Free individual texture paths
//         mlx_delete_texture(textures->north);
//         mlx_delete_texture(textures->south);
//         mlx_delete_texture(textures->west);
//         mlx_delete_texture(textures->east);
//         mlx_delete_texture(textures->floor);
//         mlx_delete_texture(textures->ceiling);
//         // Free the t_textures structure
//         free(textures);
//     }
// }

void	free_exit(t_data *data)
{
	int	i;

	i = 0;
	if (data->map->lines_arr != NULL)
		free_str_arr(data->map->lines_arr);
	while (data->map->grid[i])
	{
		free(data->map->grid[i++]);
		data->map->grid[i] = NULL;

	}
	free(data->map->grid);
	data->map->grid = NULL;
	free_texture_paths(data->map->textures_paths);
	if (data->map)
	{
		free(data->map);
		data->map = NULL;
	}
	if (data->player)
	{
		free(data->player);
		data->player = NULL;
	}
	if (data->ray)
	{
		free(data->ray);
		data->ray = NULL;
	}
	mlx_delete_image(data->mlx, data->img);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	ft_putstr_fd("Tschuess\n", 1);
	exit(0);
}
