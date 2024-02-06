/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:15:52 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 12:13:10 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (data->map->grid[i])
		free(data->map->grid[i++]);
	free(data->map->grid);
	free(data->map);
	free(data->player);
	free(data->ray);
	mlx_delete_image(data->mlx, data->img);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	ft_putstr_fd("Tschuess\n", 1);
	exit(0);
}
