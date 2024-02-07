/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:15:52 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/07 14:55:12 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures_mlx(t_textures *textures)
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

void	free_exit(t_data *data)
{
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	mlx_close_window(data->mlx);
	if (data->mlx)
		mlx_terminate(data->mlx);
	free_data(data);
	ft_putstr_fd("\nTschuess\n", 1);
	exit(0);
}