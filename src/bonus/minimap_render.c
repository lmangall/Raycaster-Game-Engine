/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:35:38 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/18 18:38:03 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap_render_background(t_data *data)
{
	int		x;
	int		y;
	t_rgba	minimap_background_color;

	x = 0;
	y = 0;
	minimap_background_color.r = 0;
	minimap_background_color.g = 0;
	minimap_background_color.b = 0;
	minimap_background_color.a = 255;
	while (y < data->minimap->height)
	{
		x = 0;
		while (x < data->minimap->width)
		{
			if (render_pixel(data->img, x, y,
					rgba_to_int(minimap_background_color)) == NULL)
				free_exit(data);
			x++;
		}
		y++;
	}
}

void	minimap_render_block(int offset_x, int offset_y, t_data *data)
{
	int	block_width_px;
	int	block_height_px;
	int	x;
	int	y;

	offset_x *= TILE_SIZE * data->minimap->scale_x;
	offset_y *= TILE_SIZE * data->minimap->scale_y;
	block_width_px = data->minimap->scale_x * TILE_SIZE + 1;
	block_height_px = data->minimap->scale_y * TILE_SIZE + 1;
	y = 0;
	while (y < block_height_px)
	{
		x = 0;
		while (x < block_width_px)
		{
			if (x + offset_x >= data->minimap->width || y
				+ offset_y >= data->minimap->height)
				break ;
			if (render_pixel(data->img, x + offset_x, y + offset_y,
					data->minimap->block_color) == NULL)
				free_exit(data);
			x++;
		}
		y++;
	}
}

void	minimap_render_walls(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (data->map->grid[y][x] == '1')
				minimap_render_block(x, y, data);
			x++;
		}
		y++;
	}
}

void	minimap_render_player(t_data *data)
{
	int	x;
	int	y;
	int	half_size;

	half_size = 3;
	y = data->minimap->player_position_y - half_size;
	while (y <= data->minimap->player_position_y + half_size)
	{
		x = data->minimap->player_position_x - half_size;
		while (x <= data->minimap->player_position_x + half_size)
		{
			if (x >= 0 && x < data->minimap->width && y >= 0
				&& y < data->minimap->height)
			{
				if (render_pixel(data->img, x, y, data->minimap->player_color)
					== NULL)
					free_exit(data);
			}
			x++;
		}
		y++;
	}
}

void	minimap_render_ray(t_data *data)
{
	int	ray_length;
	int	dx;
	int	x;
	int	y;

	ray_length = 50;
	dx = 0;
	while (dx <= ray_length)
	{
		x = data->minimap->player_position_x
			+ (int)(dx * cos(data->player->orientation_angle_rd));
		y = data->minimap->player_position_y
			+ (int)(dx * sin(data->player->orientation_angle_rd));
		if (x >= 0 && x < data->minimap->width && y >= 0
			&& y < data->minimap->height)
		{
			data->ray->screen_x = x;
			render_pixel(data->img, x, y, data->minimap->ray_color);
		}
		dx++;
	}
}
